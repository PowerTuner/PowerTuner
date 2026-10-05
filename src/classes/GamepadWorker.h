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
#pragma once
#include <QObject>
#include <QElapsedTimer>
#include <source_location>

#include "Settings.h"
#include "../extern/SDL/include/SDL3/SDL_gamepad.h"
#include "../extern/SDL/include/SDL3/SDL_events.h"
#include "../include/GamepadButton.h"

namespace PWT::App {
    class GamepadWorker final: public QObject {
        Q_OBJECT

    private:
        struct AxisState final {
            short leftX = 0;
            short leftY = 0;
            short rightX = 0;
            short rightY = 0;
        };

        static constexpr int repeatTimeout = 280;
        static constexpr int axisMax = (SDL_JOYSTICK_AXIS_MAX * 70) / 100;
        Settings &appSettings = Settings::get();
        QHash<SDL_JoystickID, std::pair<SDL_Gamepad *, QString>> gamepadsMap;
        std::pair<QString, GamepadButton> heldButton;
        QElapsedTimer *repeatTimer = nullptr;
        bool isAppFocused = false;
        AxisState axisState;

        [[nodiscard]] QString getGamepadLabel(SDL_JoystickID id) const;
        [[nodiscard]] QString getGamepadID(SDL_JoystickID id) const;
        [[nodiscard]] SDL_JoystickID getJoystickID(const QString &gamepadID) const;
        [[nodiscard]] short getAxisState(Sint16 axisValue);
        [[nodiscard]] SDL_GamepadButton getSDLButton(GamepadButton button) const;
        [[nodiscard]] SDL_GamepadAxis getSDLTrigger(GamepadButton button) const;
        void setHeldButton(const QString &gid, GamepadButton button);
        void sendHoldEvent();
        void handleEvent(const SDL_Event &evt);
        [[nodiscard]] bool isAppCombo();

    public:
        ~GamepadWorker() override;

    public slots:
        void startSDLEventsThread();
        void focusChange(bool focused);

    signals:
        void logSent(const QString &msg, std::source_location loc = std::source_location::current());
        void initFail();
        void gamepadConnected(const QString &gamepadID);
        void gamepadDisconnected(const QString &gamepadID);
        void gamepadButton(const QString &id, GamepadButton button);
    };
}
