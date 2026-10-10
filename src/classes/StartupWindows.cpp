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
#include <QApplication>

#include "StartupWindows.h"
#include "../extern/libPWTWin32/src/win32Reg.h"

namespace PWT::App {
    using namespace Qt::StringLiterals;

    StartupWindows::StartupWindows() {
        logCB = [this](const std::wstring &msg) {
            emit logSent(QString::fromStdWString(msg));
        };
    }

    bool StartupWindows::set() {
        const std::optional<bool> res = PWTREG::regKeyHasValue(HKEY_CURRENT_USER, runPath, L"Powertuner", logCB);

        if (!res)
            return false;
        else if (res.value())
            return true;

        const std::wstring appPath = uR"("%1" -s)"_s.arg(QApplication::applicationFilePath().replace('/', '\\')).toStdWString();

        return PWTREG::regWriteSZ(HKEY_CURRENT_USER, runPath, L"Powertuner", REG_SZ, appPath, logCB);
    }

    bool StartupWindows::unset() {
        const std::optional<bool> res = PWTREG::regKeyHasValue(HKEY_CURRENT_USER, runPath, L"Powertuner", logCB);

        return res && (!res.value() || PWTREG::regDeleteVal(HKEY_CURRENT_USER, runPath, L"Powertuner", logCB));
    }
}