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
            default:
                break;
        }

        return QObject::eventFilter(watched, event);
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
}