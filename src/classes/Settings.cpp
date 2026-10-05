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
    using namespace Qt::StringLiterals;

    Settings::Settings() {
        style = std::make_shared<Style::VoidPurpleStyle>();

        addLocalDaemon();
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

    void Settings::addLocalDaemon() {
        daemonList.push_back({"Local", "localhost", 56000});
    }

    void Settings::setPath(const QString &diskPath) {
        if (!diskPath.isEmpty())
            path = u"%1/settings.bin"_s.arg(diskPath);
    }

    void Settings::removeDaemon(const Daemon &d) {
        int i = 0;

        for (const Daemon &daemon: daemonList) {
            if (daemon.name == d.name)
                break;

            ++i;
        }

        daemonList.removeAt(i);

        if (defaultDaemon == i)
            defaultDaemon = 0;
    }

    GamepadMapping Settings::getGamepadMapping(const QString &gid) const {
        QMutexLocker lock(&qmux);

        return gamepadMappings.value(gid, GamepadMapping());
    }

    void Settings::setGamepadMappings(const QHash<QString, GamepadMapping> &mappings) {
        QMutexLocker lock(&qmux);

        gamepadMappings = mappings;
    }

    bool Settings::load() {
        if (path.isEmpty())
            return false;

        QFile in(path);

        if (!in.open(QFile::ReadOnly))
            return false;

        QDataStream ds(&in);

        ds >>
            daemonList >>
            gamepadMappings >>
            defaultDaemon >>
            closeToTray >>
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

        if (daemonList.isEmpty())
            addLocalDaemon();

        return true;
    }

    bool Settings::save() const {
        if (path.isEmpty())
            return false;

        QSaveFile out(path);

        if (!out.open(QSaveFile::WriteOnly))
            return false;

        QDataStream ds(&out);

        ds <<
            daemonList <<
            gamepadMappings <<
            defaultDaemon <<
            closeToTray <<
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
