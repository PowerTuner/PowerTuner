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
#include <QMouseEvent>

#include "InputHandler.h"

namespace PWT::App {
    InputHandler::InputHandler() {

    }

    bool InputHandler::eventFilter(QObject *watched, QEvent *event) {
        switch (event->type()) {
            case QEvent::KeyRelease: {
                handleKeyboardKey(static_cast<Qt::Key>(static_cast<QKeyEvent *>(event)->key()));
                return true;
            }
            case QEvent::MouseButtonRelease: {
                handleMouse(static_cast<QMouseEvent *>(event)->button());
                return true;
            }
            default:
                break;
        }

        return QObject::eventFilter(watched, event);
    }

    void InputHandler::handleKeyboardKey(const Qt::Key key) {
        if (key == appSettings.getKeyboardNavbarUp())
            emit navbarUpKey();
        else if (key == appSettings.getKeyboardNavbarDown())
            emit navbarDownKey();
        else if (key == appSettings.getKeyboardRefresh())
            emit refreshKey();
        else if (key == appSettings.getKeyboardApply())
            emit applyKey();
        else if (key == appSettings.getKeyboardUp())
            emit upKey(false);
        else if (key == appSettings.getKeyboardDown())
            emit downKey(false);
        else if (key == appSettings.getKeyboardLeft())
            emit leftKey(false);
        else if (key == appSettings.getKeyboardRight())
            emit rightKey(false);
        else if (key == appSettings.getKeyboardFastLeft())
            emit fastLeftKey(false);
        else if (key == appSettings.getKeyboardFastRight())
            emit fastRightKey(false);
        else if (key == appSettings.getKeyboardAction())
            emit actionKey(false);
        else if (key == appSettings.getKeyboardBack())
            emit backKey(false);
        else if (key == appSettings.getKeyboardScrollUp())
            emit scrollUpKey(false);
        else if (key == appSettings.getKeyboardScrollDown())
            emit scrollDownKey(false);
        else if (key == appSettings.getKeyboardScrollTop())
            emit scrollTopKey(false);
        else if (key == appSettings.getKeyboardScrollBottom())
            emit scrollBottomKey(false);
        else if (key == appSettings.getKeyboardInputMode())
            emit inputModeKey(false);
    }

    void InputHandler::handleMouse(const Qt::MouseButton btn) {
        if (btn == Qt::LeftButton)
            emit actionKey(false);
    }
}