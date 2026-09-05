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
#include <QPainter>

#include "SwitchButton.h"

namespace PWT::UI {
    SwitchButton::SwitchButton() {
        setCheckable(true);
        setFixedSize(controlW, controlH);
        setFocusPolicy(Qt::NoFocus);
    }

    void SwitchButton::paintEvent(QPaintEvent *) {
        QRect thumb(trackR.left() - thumWH2, thumbTop, thumWH, thumWH);
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        if (isChecked()) {
            thumb.moveLeft(trackR.right() - thumWH2);
            p.setPen(appTheme->switchButtonTrackActiveBorder());
            p.setBrush(appTheme->switchButtonTrackActive());

        } else {
            p.setPen(appTheme->switchButtonTrackBorder());
            p.setBrush(appTheme->switchButtonTrack());
        }

        p.drawRoundedRect(trackR, 7, 7);

        p.setPen(appTheme->switchButtonThumbBorder());
        p.setBrush(appTheme->switchButtonThumb());
        p.drawRoundedRect(thumb, 18, 18);
    }
}
