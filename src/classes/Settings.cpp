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
#include "Settings.h"
#include "../styles/VoidPurpleStyle.h"

namespace PWT::App {
    Settings &Settings::get() {
        static Settings instance;

        return instance;
    }

    std::shared_ptr<Style::Style> Settings::loadStyle(const int type) const {
        switch (static_cast<Style::StyleType>(type)) {
            default:
                return std::make_shared<Style::VoidPurpleStyle>();
        }
    }

    bool Settings::load() {
        style = loadStyle(0);
        return true;
    }

    bool Settings::save() const {
        return true;
    }

    std::shared_ptr<Style::Style> Settings::getStyle() const {
        return style;
    }
}
