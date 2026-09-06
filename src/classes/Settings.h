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
#include "../styles/Style.h"
#include "../styles/StyleType.h"

namespace PWT::App {
    class Settings final {
    private:
        Style::StyleType styleType = Style::StyleType::VoidPurple;
        std::shared_ptr<Style::Style> style;

        Settings() = default;

        [[nodiscard]] std::shared_ptr<Style::Style> loadStyle(int type) const;

    public:
        Settings(const Settings &) = delete;
        Settings &operator=(const Settings &) = delete;

        [[nodiscard]] static Settings &get();
        [[nodiscard]] bool load();
        [[nodiscard]] bool save() const;
        [[nodiscard]] std::shared_ptr<Style::Style> getStyle() const;
    };
}