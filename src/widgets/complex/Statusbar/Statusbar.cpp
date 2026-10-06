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
#include <QDesktopServices>

#include "Statusbar.h"
#include "../../components/LabelButton/LabelButton.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    Statusbar::Statusbar() {
        QHBoxLayout *lyt = new QHBoxLayout();
        LabelButton *github = new LabelButton(u"\uf09b"_s);
        QFont sbfont = font();

        sbfont.setPointSize(11);
        setFont(sbfont);
        setFocusPolicy(Qt::NoFocus);
        setToolTip(u"Sources (github)"_s);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addStretch();
        lyt->addWidget(github);

        setLayout(lyt);

        QObject::connect(github, &LabelButton::clicked, this, &Statusbar::onRepoClicked);
    }

    void Statusbar::onRepoClicked() const {
        QDesktopServices::openUrl(u"https://github.com/PowerTuner"_s);
    }
}
