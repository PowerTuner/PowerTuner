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

#include "Statusbar.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    Statusbar::Statusbar() {
        QHBoxLayout *lyt = new QHBoxLayout();
        QLabel *repo = new QLabel(uR"(<a style="color:%1" href="https://github.com/PowerTuner">Sources</a>)"_s.arg(appTheme->linkText()));
        QFont barFont = font();

        barFont.setPointSize(barFont.pointSize() - 1);
        setFont(barFont);
        repo->setTextFormat(Qt::RichText);
        repo->setTextInteractionFlags(Qt::TextBrowserInteraction);
        repo->setOpenExternalLinks(true);
        setFocusPolicy(Qt::NoFocus);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addStretch();
        lyt->addWidget(repo);

        setLayout(lyt);
    }
}
