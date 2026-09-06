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
#include <QFontMetrics>

#include "Title.h"

namespace PWT::UI {
    Title::Title(const QString &text): QLabel(text) {
        QFont lfont = font();

        lfont.setBold(true);
        lfont.setWeight(QFont::ExtraBold);
        lfont.setPointSize(lfont.pointSize() + 6);
        setFont(lfont);
        setContentsMargins(0, 5, 0, 5);
    }

    void Title::paintEvent(QPaintEvent *) {
        const QRect textRect = QFontMetrics(font()).boundingRect(text());
        const QRect bgRect {2, 0, textRect.width() + 35, textRect.height() + 4};
        QPainter p(this);

        p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        p.setPen(appTheme->titleBackground());
        p.setBrush(appTheme->titleBackground());
        p.drawRoundedRect(bgRect, 20, 20);

        p.setPen(appTheme->titleText());
        p.drawText(bgRect, Qt::AlignCenter, text());
    }
}
