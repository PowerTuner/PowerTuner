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
#include <QAbstractButton>

#include "../PInputItem.h"
#include "../../../classes/Settings.h"

namespace PWT::UI {
    class SwitchButton final: public QAbstractButton, public PInputItem {
        Q_OBJECT

    private:
        static constexpr int trackW = 44;
        static constexpr int trackH = 14;
        static constexpr int thumWH = 26;
        static constexpr int thumWH2 = thumWH / 2;
        static constexpr int controlW = trackW + thumWH + 2;
        static constexpr int controlH = thumWH + 2;
        static constexpr int trackLeft = (controlW / 2) - (trackW / 2);
        static constexpr int trackTop = (controlH / 2) - (trackH / 2);
        static constexpr int thumbTop = trackTop + (trackH / 2) - thumWH2;
        static constexpr QRect trackR {trackLeft, trackTop, trackW, trackH};
        const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();

    protected:
        void paintEvent(QPaintEvent *) override;

    public:
        SwitchButton();

        void activate(bool gamepad) override;
    };
}
