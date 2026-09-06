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

#include "NavButton.h"

namespace PWT::UI {
    NavButton::NavButton(const QString &title, const QString &icon) {
        setText(icon);
        setToolTip(title);
        setFixedSize(btnWH, btnWH);
        setFocusPolicy(Qt::NoFocus);
    }

    void NavButton::paintEvent(QPaintEvent *) {
        QPainter p(this);

        p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        paintIcon(p);

        if (isHovered || isActive) {
            p.setPen(Qt::NoPen);
            p.setBrush(isHovered ? appTheme->navButtonHovered() : appTheme->navButtonActive());
            p.drawRoundedRect(markRect, 2, 2);
        }
    }

    void NavButton::enterEvent(QEnterEvent *) {
        isHovered = true;
        update();
    }

    void NavButton::leaveEvent(QEvent *) {
        isHovered = false;
        update();
    }

    void NavButton::paintIcon(QPainter &p) const {
        p.setPen(appTheme->navButtonIcon());
        p.setBrush(appTheme->navButtonIcon());
        p.drawText(rect(), Qt::AlignCenter, text());
    }

    void NavButton::setActive(const bool active) {
        if (isActive == active) [[unlikely]]
            return;

        isActive = active;
        update();
    }
}
