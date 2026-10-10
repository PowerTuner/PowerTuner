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
#include <QKeyEvent>

#include "InputHandler.h"

namespace PWT::App {
    InputHandler::InputHandler(QObject *parent): QObject(parent) {}

    InputHandler::~InputHandler() {
        if (gamepadThread != nullptr) {
            gamepadThread->requestInterruption();
            gamepadThread->quit();
            gamepadThread->wait();
            delete gamepadWorker;
            delete gamepadThread;
        }
    }

    bool InputHandler::eventFilter(QObject *watched, QEvent *event) {
        switch (event->type()) {
            case QEvent::KeyRelease: {
                const QKeyEvent *kevt = static_cast<QKeyEvent *>(event);

                if (!kevt->isAutoRepeat())
                    handleKeyboardReleaseKey(static_cast<Qt::Key>(kevt->key()));

                return true;
            }
            case QEvent::KeyPress: {
                handleKeyboardPressKey(static_cast<Qt::Key>(static_cast<QKeyEvent *>(event)->key()));
                return true;
            }
            case QEvent::WindowActivate:
            case QEvent::WindowDeactivate: {
                emit appFocusChange(event->type() == QEvent::WindowActivate);
            }
                break;
            default:
                break;
        }

        return QObject::eventFilter(watched, event);
    }

    void InputHandler::startGamepadThread() {
        gamepadThread = new QThread();
        gamepadWorker = new GamepadWorker();

        gamepadWorker->moveToThread(gamepadThread);

        QObject::connect(gamepadThread, &QThread::started, gamepadWorker, &GamepadWorker::startSDLEventsThread);
        QObject::connect(gamepadWorker, &GamepadWorker::logSent, this, &InputHandler::logSent);
        QObject::connect(gamepadWorker, &GamepadWorker::initFail, this, &InputHandler::onSDLInitFail);
        QObject::connect(gamepadWorker, &GamepadWorker::gamepadConnected, this, &InputHandler::gamepadConnected);
        QObject::connect(gamepadWorker, &GamepadWorker::gamepadDisconnected, this, &InputHandler::gamepadDisconnected);
        QObject::connect(gamepadWorker, &GamepadWorker::gamepadButton, this, &InputHandler::onGamepadButton);
        QObject::connect(this, &InputHandler::appFocusChange, gamepadWorker, &GamepadWorker::focusChange);

        gamepadThread->start();
    }

    void InputHandler::handleKeyboardReleaseKey(const Qt::Key key) {
        if (key == appSettings.getKeyboardNavbarUp())
            emit navbarUpKey();
        else if (key == appSettings.getKeyboardNavbarDown())
            emit navbarDownKey();
        else if (key == appSettings.getKeyboardRefresh())
            emit refreshKey();
        else if (key == appSettings.getKeyboardApply())
            emit applyKey();
        else if (key == appSettings.getKeyboardAction())
            emit buttonPressed(ButtonKey::Action, false);
        else if (key == appSettings.getKeyboardBack())
            emit buttonPressed(ButtonKey::Back, false);
        else if (key == appSettings.getKeyboardScrollTop())
            emit buttonPressed(ButtonKey::ScrollTop, false);
        else if (key == appSettings.getKeyboardScrollBottom())
            emit buttonPressed(ButtonKey::ScrollBottom, false);
        else if (key == appSettings.getKeyboardInputMode())
            emit buttonPressed(ButtonKey::InputMode, false);
    }

    void InputHandler::handleKeyboardPressKey(const Qt::Key key) {
        if (key == appSettings.getKeyboardUp())
            emit buttonPressed(ButtonKey::Up, false);
        else if (key == appSettings.getKeyboardDown())
            emit buttonPressed(ButtonKey::Down, false);
        else if (key == appSettings.getKeyboardLeft())
            emit buttonPressed(ButtonKey::Left, false);
        else if (key == appSettings.getKeyboardRight())
            emit buttonPressed(ButtonKey::Right, false);
        else if (key == appSettings.getKeyboardFastLeft())
            emit buttonPressed(ButtonKey::FastLeft, false);
        else if (key == appSettings.getKeyboardFastRight())
            emit buttonPressed(ButtonKey::FastRight, false);
        else if (key == appSettings.getKeyboardScrollUp())
            emit buttonPressed(ButtonKey::ScrollUp, false);
        else if (key == appSettings.getKeyboardScrollDown())
            emit buttonPressed(ButtonKey::ScrollDown, false);
    }

    void InputHandler::onSDLInitFail() {
        gamepadThread->quit();
        gamepadThread->wait();
        delete gamepadWorker;
        delete gamepadThread;

        gamepadThread = nullptr;
        gamepadWorker = nullptr;
    }

    void InputHandler::onGamepadButton(const QString &gid, const GamepadButton button) {
        const GamepadMapping mapping = appSettings.getGamepadMapping(gid);

        if (button == mapping.navbarUp)
            emit navbarUpKey();
        else if (button == mapping.navbarDown)
            emit navbarDownKey();
        else if (button == mapping.refresh)
            emit refreshKey();
        else if (button == mapping.apply)
            emit applyKey();
        else if (button == mapping.action)
            emit buttonPressed(ButtonKey::Action, true);
        else if (button == mapping.back)
            emit buttonPressed(ButtonKey::Back, true);
        else if (button == mapping.up)
            emit buttonPressed(ButtonKey::Up, true);
        else if (button == mapping.down)
            emit buttonPressed(ButtonKey::Down, true);
        else if (button == mapping.left)
            emit buttonPressed(ButtonKey::Left, true);
        else if (button == mapping.right)
            emit buttonPressed(ButtonKey::Right, true);
        else if (button == mapping.fastLeft)
            emit buttonPressed(ButtonKey::FastLeft, true);
        else if (button == mapping.fastRight)
            emit buttonPressed(ButtonKey::FastRight, true);
        else if (button == mapping.scrollUp)
            emit buttonPressed(ButtonKey::ScrollUp, true);
        else if (button == mapping.scrollDown)
            emit buttonPressed(ButtonKey::ScrollDown, true);
        else if (button == mapping.scrollTop)
            emit buttonPressed(ButtonKey::ScrollTop, true);
        else if (button == mapping.scrollBottom)
            emit buttonPressed(ButtonKey::ScrollBottom, true);
        else if (button == mapping.inputMode)
            emit buttonPressed(ButtonKey::InputMode, true);
        else if (button == GamepadButton::APP_COMBO)
            emit toggleAppWindow();
    }
}
