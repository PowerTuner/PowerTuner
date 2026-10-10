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
#include "Factories.h"
#ifdef __linux__
#include "classes/StartupLinux.h"
#elifdef _WIN32
#include "classes/StartupWindows.h"
#endif

namespace PWT {
    App::Startup &startupFactory() {
#ifdef __linux__
        static App::StartupLinux instance;
#elifdef _WIN32
        static App::StartupWindows instance;
#endif
        return instance;
    }
}
