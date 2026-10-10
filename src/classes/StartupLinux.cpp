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
#include <QStandardPaths>
#include <QSaveFile>
#include <QApplication>
#include <QFile>

#include "StartupLinux.h"

namespace PWT::App {
    using namespace Qt::StringLiterals;

    StartupLinux::StartupLinux() {
        desktopPath = u"%1/.config/autostart/powertuner.desktop"_s.arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    }

    bool StartupLinux::set() {
        QSaveFile desktop{desktopPath};
        QTextStream ts{&desktop};

        if (!desktop.open(QSaveFile::WriteOnly | QSaveFile::Truncate | QSaveFile::Text))
            return false;

        ts << "[Desktop Entry]\n" <<
            "Categories=System\n" <<
            "Name=Powertuner\n" <<
            "StartupNotify=false\n" <<
            "Terminal=false\n" <<
            "Type=Application\n" <<
            "Icon=/usr/icon/hicolor/powertuner.ico\n" <<
            u"Exec=%1 -s\n"_s.arg(QApplication::applicationFilePath());

        return desktop.commit();
    }

    bool StartupLinux::unset() {
        QFile desktop{desktopPath};

        return !desktop.exists() || desktop.remove();
    }
}