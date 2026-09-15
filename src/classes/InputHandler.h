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
#include "../include/ButtonKey.h"

namespace PWT::App {
    class InputHandler final: public QObject {
        Q_OBJECT

    private:
        Settings &appSettings = Settings::get();

        void handleKeyboardReleaseKey(Qt::Key key);
        void handleKeyboardPressKey(Qt::Key key);

    public:
        explicit InputHandler(QObject *parent);

        bool eventFilter(QObject *watched, QEvent *event) override;

    signals:
        void navbarUpKey();
        void navbarDownKey();
        void refreshKey();
        void applyKey();
        void buttonPressed(ButtonKey key, bool gamepad);
    };
}