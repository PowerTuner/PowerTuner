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
#include <QStyleOptionSlider>

#include "Scrollbar.h"
#include "../../../classes/Settings.h"

namespace PWT::UI {
    Scrollbar::Scrollbar(const Qt::Orientation orientation): QScrollBar(orientation) {}

    void Scrollbar::paintEvent(QPaintEvent *) {
        QStyleOptionSlider opt;

        initStyleOption(&opt);

        const QRect bar = style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this);
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(Qt::NoPen);
        p.setBrush(appTheme->scrollbar());
        p.drawRoundedRect(bar, 6, 6);
    }

    QSize Scrollbar::sizeHint() const {
        QSize size = QScrollBar::sizeHint();

        if (orientation() == Qt::Vertical)
            size.setWidth(6);
        else
            size.setHeight(6);

        return size;
    }
}
