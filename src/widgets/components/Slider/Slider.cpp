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
#include <QPainter>
#include <QStyleOptionSlider>

#include "Slider.h"

namespace PWT::UI {
    Slider::Slider() {
        setOrientation(Qt::Horizontal);
        setMinimum(0);
        setMaximum(100);
        setMinimumSize(100, thumbWH + 2);
        setFocusPolicy(Qt::NoFocus);
    }

    void Slider::paintEvent(QPaintEvent *) {
        QStyleOptionSlider opt;

        initStyleOption(&opt);

        const QRect _track = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
        const QRect _thumb = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        const QRect track(_track.left(), _track.center().y() - trackH2, _track.width(), trackH);
        const int thumbX = QStyle::sliderPositionFromValue(minimum(), maximum(), value(), track.width() - thumbWH, opt.upsideDown) + track.left();
        const QRect thumb(thumbX, _thumb.center().y() - thumbWH2, thumbWH, thumbWH);
        const QRect activeTrack(track.left(), track.top(), thumb.x() + thumbWH2, track.height());
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(appTheme->sliderTrackBorder());
        p.setBrush(appTheme->sliderTrack());
        p.drawRoundedRect(track, 6, 6);

        p.setPen(appTheme->sliderTrackActiveBorder());
        p.setBrush(appTheme->sliderTrackActive());
        p.drawRoundedRect(activeTrack, 6, 6);

        p.setPen(appTheme->sliderThumbBorder());
        p.setBrush(appTheme->sliderThumb());
        p.drawRoundedRect(thumb, 15, 15);
    }
}
