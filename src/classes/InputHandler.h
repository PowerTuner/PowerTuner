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

#include "Settings.h"

namespace PWT::App {
    class InputHandler: public QObject {
        Q_OBJECT

    private:
        Settings &appSettings = Settings::get();

        void handleKeyboardKey(Qt::Key key);
        void handleMouse(Qt::MouseButton btn);

    public:
        InputHandler();

        bool eventFilter(QObject *watched, QEvent *event) override;

    signals:
        void navbarUpKey();
        void navbarDownKey();
        void refreshKey();
        void applyKey();
        void upKey(bool gamepad);
        void downKey(bool gamepad);
        void leftKey(bool gamepad);
        void rightKey(bool gamepad);
        void fastLeftKey(bool gamepad);
        void fastRightKey(bool gamepad);
        void actionKey(bool gamepad);
        void backKey(bool gamepad);
        void scrollUpKey(bool gamepad);
        void scrollDownKey(bool gamepad);
        void scrollTopKey(bool gamepad);
        void scrollBottomKey(bool gamepad);
        void inputModeKey(bool gamepad);
    };
}