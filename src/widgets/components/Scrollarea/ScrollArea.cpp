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
#include <QScroller>

#include "ScrollArea.h"
#include "Scrollbar.h"

namespace PWT::UI {
    ScrollArea::ScrollArea(const bool noBars) {
        QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);
        removeBackground();
        setWidgetResizable(true);
        setWidget(new QWidget);
        setFocusPolicy(Qt::NoFocus);

        if (noBars) {
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        } else {
            setVerticalScrollBar(new Scrollbar(Qt::Vertical));
            setHorizontalScrollBar(new Scrollbar(Qt::Horizontal));
        }
    }

    ScrollArea::ScrollArea(const Qt::Orientation orientation, const bool noBars) {
        QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);
        removeBackground();
        setWidgetResizable(true);
        setWidget(new QWidget);
        setFocusPolicy(Qt::NoFocus);

        if (orientation == Qt::Horizontal) {
            if (noBars)
                setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            else
                setHorizontalScrollBar(new Scrollbar(Qt::Horizontal));

            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        } else {
            if (noBars)
                setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            else
                setVerticalScrollBar(new Scrollbar(Qt::Vertical));

            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    void ScrollArea::removeBackground() {
        QPalette pal = palette();

        pal.setColor(QPalette::Window, Qt::transparent);
        pal.setColor(QPalette::Base, Qt::transparent);
        setPalette(pal);

        setFrameShape(QFrame::NoFrame);
        setAutoFillBackground(false);
        viewport()->setAutoFillBackground(false);
        viewport()->setAttribute(Qt::WA_TranslucentBackground);
    }
}
