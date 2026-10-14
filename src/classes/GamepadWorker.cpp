/*
 * This file is part of PowerTuner.
 * Copyright (C) 2026 kylon
 *
 * PowerTuner is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PowerTuner is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QCoreApplication>
#include <QThread>

#include "GamepadWorker.h"
#include "../extern/SDL/include/SDL3/SDL_init.h"
#include "../extern/SDL/include/SDL3/SDL_hints.h"

namespace PWT::App {
    using namespace Qt::StringLiterals;

    GamepadWorker::~GamepadWorker() {
        delete repeatTimer;

        for (const auto &[sdlPad, gid]: gamepadsMap)
            SDL_CloseGamepad(sdlPad);

        SDL_Quit();
    }

    QString GamepadWorker::getGamepadLabel(const SDL_JoystickID id) const {
        QString name = SDL_GetGamepadNameForID(id);

        if (name.isEmpty()) [[unlikely]] {
            const SDL_GamepadType type = SDL_GetGamepadTypeForID(id);

            name = SDL_GetGamepadStringForType(type);

            if (type == SDL_GAMEPAD_TYPE_UNKNOWN || name.isEmpty())
                return "Generic";
        }

        return name;
    }

    QString GamepadWorker::getGamepadID(const SDL_JoystickID id) const {
        const QString label = getGamepadLabel(id);
        constexpr int sz = 40;
        char buf[sz] = {0};
        char guid[sz] = {0};
        int idx = 0;

        SDL_GUIDToString(SDL_GetGamepadGUIDForID(id), buf, sz);

        while (true) {
            snprintf(guid, sz, "%s%d", buf, idx++);

            auto it = std::find_if(gamepadsMap.constBegin(), gamepadsMap.constEnd(), [guid](const std::pair<SDL_Gamepad *, QString> &gp)->bool {
                return gp.second == guid;
            });

            if (it == gamepadsMap.constEnd()) [[likely]]
                break;
        }

        return u"%1[%2]"_s.arg(label, guid);
    }

    SDL_JoystickID GamepadWorker::getJoystickID(const QString &gamepadID) const {
        if (gamepadID.isEmpty())
            return 0;

        for (const auto &[jid, gpad]: gamepadsMap.asKeyValueRange()) {
            if (gpad.second == gamepadID)
                return jid;
        }

        return 0;
    }

    short GamepadWorker::getAxisState(const Sint16 axisValue) {
        if (axisValue >= -axisMax && axisValue <= axisMax) // deadzone
            return 0;

        return axisValue > 0 ? 1 : -1;
    }

    SDL_GamepadButton GamepadWorker::getSDLButton(const GamepadButton button) const {
        switch (button) {
            case GamepadButton::SOUTH:
                return SDL_GAMEPAD_BUTTON_SOUTH;
            case GamepadButton::EAST:
                return SDL_GAMEPAD_BUTTON_EAST;
            case GamepadButton::WEST:
                return SDL_GAMEPAD_BUTTON_WEST;
            case GamepadButton::NORTH:
                return SDL_GAMEPAD_BUTTON_NORTH;
            case GamepadButton::DPAD_UP:
                return SDL_GAMEPAD_BUTTON_DPAD_UP;
            case GamepadButton::DPAD_DOWN:
                return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
            case GamepadButton::DPAD_LEFT:
                return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
            case GamepadButton::DPAD_RIGHT:
                return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
            case GamepadButton::SELECT:
                return SDL_GAMEPAD_BUTTON_BACK;
            case GamepadButton::START:
                return SDL_GAMEPAD_BUTTON_START;
            case GamepadButton::HOME:
                return SDL_GAMEPAD_BUTTON_GUIDE;
            case GamepadButton::MISC:
                return SDL_GAMEPAD_BUTTON_MISC1;
            case GamepadButton::UP_LEFT_PADDLE:
                return SDL_GAMEPAD_BUTTON_LEFT_PADDLE1;
            case GamepadButton::LOW_LEFT_PADDLE:
                return SDL_GAMEPAD_BUTTON_LEFT_PADDLE2;
            case GamepadButton::UP_RIGHT_PADDLE:
                return SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1;
            case GamepadButton::LOW_RIGHT_PADDLE:
                return SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2;
            case GamepadButton::L1:
                return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;
            case GamepadButton::L3:
                return SDL_GAMEPAD_BUTTON_LEFT_STICK;
            case GamepadButton::R1:
                return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;
            case GamepadButton::R3:
                return SDL_GAMEPAD_BUTTON_RIGHT_STICK;
            default:
                return SDL_GAMEPAD_BUTTON_INVALID;
        }
    }

    SDL_GamepadAxis GamepadWorker::getSDLTrigger(const GamepadButton button) const {
        switch (button) {
            case GamepadButton::L2:
                return SDL_GAMEPAD_AXIS_LEFT_TRIGGER;
            case GamepadButton::R2:
                return SDL_GAMEPAD_AXIS_RIGHT_TRIGGER;
            default:
                return SDL_GAMEPAD_AXIS_INVALID;
        }
    }

    void GamepadWorker::setHeldButton(const QString &gid, const GamepadButton button) {
        if (repeatTimer->isValid() && button == heldButton.second)
            return;

        heldButton = std::make_pair(gid, button);

        emit gamepadButton(gid, button);
        repeatTimer->start();
    }

    void GamepadWorker::sendHoldEvent() {
        if (!repeatTimer->hasExpired(repeatTimeout))
            return;

        emit gamepadButton(heldButton.first, heldButton.second);
        repeatTimer->start();
    }

    void GamepadWorker::handleEvent(const SDL_Event &evt) {
        switch (evt.type) {
            case SDL_EVENT_GAMEPAD_ADDED: {
                if (gamepadsMap.contains(evt.gdevice.which)) [[unlikely]]
                    break; // if duplicate event, skip

                const SDL_JoystickID id = evt.gdevice.which;
                const QString guid = getGamepadID(id);
                SDL_Gamepad *pad = SDL_OpenGamepad(id);

                if (pad == nullptr) {
                    emit logSent(u"gamepad connection error: %1"_s.arg(SDL_GetError()));
                    SDL_ClearError();

                } else {
                    gamepadsMap.insert(id, std::make_pair(pad, guid));
                    emit gamepadConnected(guid);
                }
            }
                break;
            case SDL_EVENT_GAMEPAD_REMOVED: {
                if (!gamepadsMap.contains(evt.gdevice.which)) [[unlikely]]
                    break;

                const auto &[sdlPad, gid] = gamepadsMap.take(evt.gdevice.which);

                SDL_CloseGamepad(sdlPad);
                emit gamepadDisconnected(gid);
            }
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_UP: {
                if (!isAppFocused)
                    break;

                const auto it = gamepadsMap.constFind(evt.gdevice.which);

                if (it == gamepadsMap.constEnd()) [[unlikely]]
                    break;

                switch (evt.gbutton.button) {
                    case SDL_GAMEPAD_BUTTON_SOUTH:
                        emit gamepadButton(it->second, GamepadButton::SOUTH);
                        break;
                    case SDL_GAMEPAD_BUTTON_EAST:
                        emit gamepadButton(it->second, GamepadButton::EAST);
                        break;
                    case SDL_GAMEPAD_BUTTON_WEST:
                        emit gamepadButton(it->second, GamepadButton::WEST);
                        break;
                    case SDL_GAMEPAD_BUTTON_NORTH:
                        emit gamepadButton(it->second, GamepadButton::NORTH);
                        break;
                    case SDL_GAMEPAD_BUTTON_START:
                        emit gamepadButton(it->second, GamepadButton::START);
                        break;
                    case SDL_GAMEPAD_BUTTON_BACK:
                        emit gamepadButton(it->second, GamepadButton::SELECT);
                        break;
                    case SDL_GAMEPAD_BUTTON_GUIDE:
                        emit gamepadButton(it->second, GamepadButton::HOME);
                        break;
                    case SDL_GAMEPAD_BUTTON_MISC1:
                        emit gamepadButton(it->second, GamepadButton::MISC);
                        break;
                    case SDL_GAMEPAD_BUTTON_LEFT_PADDLE1:
                        emit gamepadButton(it->second, GamepadButton::UP_LEFT_PADDLE);
                        break;
                    case SDL_GAMEPAD_BUTTON_LEFT_PADDLE2:
                        emit gamepadButton(it->second, GamepadButton::LOW_LEFT_PADDLE);
                        break;
                    case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1:
                        emit gamepadButton(it->second, GamepadButton::UP_RIGHT_PADDLE);
                        break;
                    case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2:
                        emit gamepadButton(it->second, GamepadButton::LOW_RIGHT_PADDLE);
                        break;
                    case SDL_GAMEPAD_BUTTON_LEFT_STICK:
                        emit gamepadButton(it->second, GamepadButton::L3);
                        break;
                    case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
                        emit gamepadButton(it->second, GamepadButton::R3);
                        break;
                    case SDL_GAMEPAD_BUTTON_DPAD_UP:
                    case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
                    case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
                    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
                    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
                    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
                        repeatTimer->invalidate();
                        break;
                    default:
                        break;
                }
            }
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN: {
                if (!isAppFocused)
                    break;

                const auto it = gamepadsMap.constFind(evt.gdevice.which);

                if (it == gamepadsMap.constEnd()) [[unlikely]]
                    break;

                switch (evt.gbutton.button) {
                    case SDL_GAMEPAD_BUTTON_DPAD_UP:
                        setHeldButton(it->second, GamepadButton::DPAD_UP);
                        break;
                    case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
                        setHeldButton(it->second, GamepadButton::DPAD_DOWN);
                        break;
                    case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
                        setHeldButton(it->second, GamepadButton::DPAD_LEFT);
                        break;
                    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
                        setHeldButton(it->second, GamepadButton::DPAD_RIGHT);
                        break;
                    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
                        setHeldButton(it->second, GamepadButton::L1);
                        break;
                    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
                        setHeldButton(it->second, GamepadButton::R1);
                        break;
                    default:
                        break;
                }
            }
                break;
            case SDL_EVENT_GAMEPAD_AXIS_MOTION: {
                if (!isAppFocused)
                    break;

                const auto it = gamepadsMap.constFind(evt.gaxis.which);

                if (it == gamepadsMap.constEnd()) [[unlikely]]
                    break;

                switch (evt.gaxis.axis) {
                    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER: {
                        if (evt.gaxis.value < axisMax)
                            repeatTimer->invalidate();
                        else if (evt.gaxis.value >= axisMax)
                            setHeldButton(it->second, GamepadButton::L2);
                    }
                        break;
                    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: {
                        if (evt.gaxis.value < axisMax)
                            repeatTimer->invalidate();
                        else if (evt.gaxis.value >= axisMax)
                            setHeldButton(it->second, GamepadButton::R2);
                    }
                        break;
                    case SDL_GAMEPAD_AXIS_LEFTX: {
                        const short old = axisState.leftX;

                        axisState.leftX = getAxisState(evt.gaxis.value);

                        if (old == axisState.leftX)
                            break;
                        else if (axisState.leftY != 0 || (axisState.leftX == 0 && (heldButton.second == GamepadButton::ANALOG_LEFT_LEFT || heldButton.second == GamepadButton::ANALOG_LEFT_RIGHT)))
                            repeatTimer->invalidate();
                        else if (axisState.leftX > 0)
                            setHeldButton(it->second, GamepadButton::ANALOG_LEFT_RIGHT);
                        else
                            setHeldButton(it->second, GamepadButton::ANALOG_LEFT_LEFT);
                    }
                        break;
                    case SDL_GAMEPAD_AXIS_LEFTY: {
                        const short old = axisState.leftY;

                        axisState.leftY = getAxisState(evt.gaxis.value);

                        if (old == axisState.leftY)
                            break;
                        if (axisState.leftX != 0 || (axisState.leftY == 0 && (heldButton.second == GamepadButton::ANALOG_LEFT_DOWN || heldButton.second == GamepadButton::ANALOG_LEFT_UP)))
                            repeatTimer->invalidate();
                        else if (axisState.leftY > 0)
                            setHeldButton(it->second, GamepadButton::ANALOG_LEFT_DOWN);
                        else
                            setHeldButton(it->second, GamepadButton::ANALOG_LEFT_UP);
                    }
                        break;
                    case SDL_GAMEPAD_AXIS_RIGHTX: {
                        const short old = axisState.rightX;

                        axisState.rightX = getAxisState(evt.gaxis.value);

                        if (old == axisState.rightX)
                            break;
                        if (axisState.rightY != 0 || (axisState.rightX == 0 && (heldButton.second == GamepadButton::ANALOG_RIGHT_RIGHT || heldButton.second == GamepadButton::ANALOG_RIGHT_LEFT)))
                            repeatTimer->invalidate();
                        else if (axisState.rightX > 0)
                            setHeldButton(it->second, GamepadButton::ANALOG_RIGHT_RIGHT);
                        else
                            setHeldButton(it->second, GamepadButton::ANALOG_RIGHT_LEFT);
                    }
                        break;
                    case SDL_GAMEPAD_AXIS_RIGHTY: {
                        const short old = axisState.rightY;

                        axisState.rightY = getAxisState(evt.gaxis.value);

                        if (old == axisState.rightY)
                            break;
                        if (axisState.rightX != 0 || (axisState.rightY == 0 && (heldButton.second == GamepadButton::ANALOG_RIGHT_DOWN || heldButton.second == GamepadButton::ANALOG_RIGHT_UP)))
                            repeatTimer->invalidate();
                        else if (axisState.rightY > 0)
                            setHeldButton(it->second, GamepadButton::ANALOG_RIGHT_DOWN);
                        else
                            setHeldButton(it->second, GamepadButton::ANALOG_RIGHT_UP);
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
            default:
                break;
        }
    }

    bool GamepadWorker::isAppCombo() {
        for (const auto &[sdlPad, gid]: gamepadsMap) {
            const GamepadMapping map = appSettings.getGamepadMapping(gid);
            const SDL_GamepadButton s1 = getSDLButton(map.appComboSlot1);
            const SDL_GamepadAxis s1a = getSDLTrigger(map.appComboSlot1);
            const SDL_GamepadButton s2 = getSDLButton(map.appComboSlot2);
            const SDL_GamepadAxis s2a = getSDLTrigger(map.appComboSlot2);
            const SDL_GamepadButton s3 = getSDLButton(map.appComboSlot3);
            const SDL_GamepadAxis s3a = getSDLTrigger(map.appComboSlot3);

            if ((SDL_GetGamepadButton(sdlPad, s1) || SDL_GetGamepadAxis(sdlPad, s1a) >= axisMax) &&
                (SDL_GetGamepadButton(sdlPad, s2) || SDL_GetGamepadAxis(sdlPad, s2a) >= axisMax) &&
                (SDL_GetGamepadButton(sdlPad, s3) || SDL_GetGamepadAxis(sdlPad, s3a) >= axisMax))
            {
                QThread::msleep(140);
                emit gamepadButton(gid, GamepadButton::APP_COMBO);
                return true;
            }
        }

        return false;
    }

    void GamepadWorker::startSDLEventsThread() {
        repeatTimer = new QElapsedTimer();

        SDL_SetHint(SDL_HINT_JOYSTICK_ENHANCED_REPORTS, "0");
        repeatTimer->invalidate();

        if (!SDL_Init(SDL_INIT_GAMEPAD)) {
            emit logSent(u"failed to init SDL gamepad subsystem"_s);
            emit initFail();
            return;
        }

        emit initOk();

        while (!QThread::currentThread()->isInterruptionRequested()) {
            SDL_Event evt;

            if (isAppCombo()) {
                repeatTimer->invalidate();
                SDL_PumpEvents();
                SDL_FlushEvents(SDL_EVENT_GAMEPAD_AXIS_MOTION, SDL_EVENT_GAMEPAD_BUTTON_UP);

            } else {
                if (repeatTimer->isValid())
                    sendHoldEvent();

                while (SDL_PollEvent(&evt))
                    handleEvent(evt);
            }

            QCoreApplication::processEvents();
            QThread::msleep(15);
        }
    }

    void GamepadWorker::focusChange(const bool focused) {
        isAppFocused = focused;
    }
}
