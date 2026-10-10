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
#include <QThread>

#include "Settings.h"
#include "../include/ButtonKey.h"
#include "GamepadWorker.h"

namespace PWT::App {
    class InputHandler final: public QObject {
        Q_OBJECT

    private:
        Settings &appSettings = Settings::get();
        GamepadWorker *gamepadWorker = nullptr;
        QThread *gamepadThread = nullptr;

        void handleKeyboardReleaseKey(Qt::Key key);
        void handleKeyboardPressKey(Qt::Key key);

    public:
        explicit InputHandler(QObject *parent);
        ~InputHandler() override;

        bool eventFilter(QObject *watched, QEvent *event) override;
        void startGamepadThread();

    private slots:
        void onSDLInitFail();
        void onGamepadButton(const QString &gid, GamepadButton button);

    signals:
        void logSent(const QString &msg, std::source_location loc = std::source_location::current());
        void navbarUpKey();
        void navbarDownKey();
        void refreshKey();
        void applyKey();
        void buttonPressed(ButtonKey key, bool gamepad);
        void appFocusChange(bool focused);
        void gamepadConnected(const QString &gid);
        void gamepadDisconnected(const QString &gid);
        void toggleAppWindow();
    };
}