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
#include <QFile>
#include <QSaveFile>
#include <QDataStream>

#include "Settings.h"
#include "../styles/VoidPurpleStyle.h"

namespace PWT::App {
    Settings::Settings() {
        style = std::make_shared<Style::VoidPurpleStyle>();
    }

    Settings &Settings::get() {
        static Settings instance;

        return instance;
    }

    void Settings::loadStyle() {
        switch (styleType) {
            default:
                break;
        }
    }

    void Settings::setPath(const QString &diskPath) {
        if (!diskPath.isEmpty())
            path = QString("%1/settings.bin").arg(diskPath);
    }

    bool Settings::load() {
        if (path.isEmpty())
            return false;

        QFile in(path);

        if (!in.open(QFile::ReadOnly))
            return false;

        QDataStream ds(&in);

        ds >> closeToTray >>
            rememberWindowState >>
            runAtStartup >>
            styleType >>
            kbNavbarUp >>
            kbNavbarDown >>
            kbRefresh >>
            kbApply >>
            kbUp >>
            kbDown >>
            kbLeft >>
            kbRight >>
            kbFastLeft >>
            kbFastRight >>
            kbAction >>
            kbBack >>
            kbScrollUp >>
            kbScrollDown >>
            kbScrollTop >>
            kbScrollBottom >>
            kbInputMode;

        in.close();
        loadStyle();
        return true;
    }

    bool Settings::save() const {
        if (path.isEmpty())
            return false;

        QSaveFile out(path);

        if (!out.open(QSaveFile::WriteOnly))
            return false;

        QDataStream ds(&out);

        ds << closeToTray <<
            rememberWindowState <<
            runAtStartup <<
            styleType <<
            kbNavbarUp <<
            kbNavbarDown <<
            kbRefresh <<
            kbApply <<
            kbUp <<
            kbDown <<
            kbLeft <<
            kbRight <<
            kbFastLeft <<
            kbFastRight <<
            kbAction <<
            kbBack <<
            kbScrollUp <<
            kbScrollDown <<
            kbScrollTop <<
            kbScrollBottom <<
            kbInputMode;

        return out.commit();
    }
}
