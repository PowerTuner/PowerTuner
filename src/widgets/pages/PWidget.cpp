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

#include "PWidget.h"

namespace PWT::UI {
    PWidget::PWidget() {
        setFocusPolicy(Qt::NoFocus);
        setContentsMargins(6,6,6,6);
    }

    void PWidget::paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);

        if (isFocused || isHovered) {
            const QPen border(appTheme->pwidgetFocused(), 2);
            QPainter p(this);

            p.setPen(border);
            p.setBrush(Qt::NoBrush);
            p.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8);
        }
    }

    void PWidget::enterEvent(QEnterEvent *) {
        isHovered = true;
        update();
    }

    void PWidget::leaveEvent(QEvent *) {
        isHovered = false;
        update();
    }
}
