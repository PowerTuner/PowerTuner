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
  * adouble with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <QSlider>

#include "../../../classes/Settings.h"

namespace PWT::UI {
    class Slider final: public QSlider {
        Q_OBJECT

    private:
        static constexpr int trackH = 10;
        static constexpr int trackH2 = trackH / 2;
        static constexpr int thumbWH = 26;
        static constexpr int thumbWH2 = thumbWH / 2;
        static constexpr int thumbT2 = trackH2 - thumbWH2;
        const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();

    protected:
        void paintEvent(QPaintEvent *) override;

    public:
        Slider();
    };
}