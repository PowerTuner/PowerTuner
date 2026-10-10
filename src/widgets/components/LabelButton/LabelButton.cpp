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
#include <QMouseEvent>

#include "LabelButton.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    LabelButton::LabelButton(const QString& text): QLabel(text) {
        QFont lFont = font();

        lFont.setFamily(u"Font Awesome 7 Free"_s);
        setFont(lFont);
    }

    void LabelButton::mouseReleaseEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton)
            emit clicked();

        event->accept();
    }

    void LabelButton::enterEvent(QEnterEvent *) {
        setCursor(QCursor(Qt::PointingHandCursor));
    }

    void LabelButton::leaveEvent(QEvent *) {
        setCursor(QCursor(Qt::ArrowCursor));
    }
}
