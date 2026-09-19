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
#include <QMouseEvent>

#include "Button.h"

namespace PWT::UI {
    Button::Button(const QString &text, const bool rounded): QPushButton(text), PInputItem(this) {
        isRounded = rounded;

        setFocusPolicy(Qt::NoFocus);
    }

    void Button::paintEvent(QPaintEvent *) {
        const QRect btnRect = rect();
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(isFocused ? QPen(appTheme->focusBorder(), 2) : appTheme->buttonBorder());
        p.setBrush(isHovered ? appTheme->buttonHovered() : appTheme->button());

        if (isRounded)
            p.drawRoundedRect(btnRect, 5, 5);
        else
            p.drawRect(btnRect);

        p.setPen(appTheme->buttonLabel());
        p.drawText(btnRect, Qt::AlignCenter, text());
    }

    void Button::enterEvent(QEnterEvent *) {
        isHovered = true;
        update();
    }

    void Button::leaveEvent(QEvent *) {
        isHovered = false;
        update();
    }

    void Button::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            isHovered = false;
            update();
        }

        QPushButton::mousePressEvent(event);
    }

    void Button::mouseReleaseEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton && rect().contains(event->position().toPoint())) {
            isHovered = true;
            update();
        }

        QPushButton::mouseReleaseEvent(event);
    }

    void Button::activate() {
        emit clicked();
    }
}
