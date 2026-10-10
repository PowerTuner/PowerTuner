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
#include <QHBoxLayout>
#include <QPainter>
#include <QLabel>

#include "Title.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    Title::Title(const QString &text, const QString &icon) {
        QHBoxLayout *lyt = new QHBoxLayout();
        QLabel *icn = new QLabel(icon);
        QLabel *lbl = new QLabel(text);
        QFont lfont = font();
        QFont icfont = font();
        QPalette pal = palette();

        pal.setColor(QPalette::WindowText, appTheme->titleText());
        lfont.setBold(true);
        lfont.setWeight(QFont::ExtraBold);
        lfont.setPointSize(lfont.pointSize() + 6);
        lbl->setFont(lfont);
        icfont.setPointSize(icfont.pointSize() + 6);
        icfont.setFamily(u"Font Awesome 7 Free"_s);
        icn->setFont(icfont);

        lyt->addWidget(icn);
        lyt->addWidget(lbl);

        setPalette(pal);
        setLayout(lyt);
    }

    void Title::paintEvent(QPaintEvent *) {
        QPainter p(this);

        p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        p.setPen(appTheme->titleBackground());
        p.setBrush(appTheme->titleBackground());
        p.drawRoundedRect(rect(), 20, 20);
    }
}
