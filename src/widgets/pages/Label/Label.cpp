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

#include "Label.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    Label::Label(const QString &title, const QString &text) {
        QHBoxLayout *lyt = new QHBoxLayout();

        lbl = new QLabel(text.isEmpty() ? u"-"_s : text);

        lyt->addWidget(new QLabel(title));
        lyt->addStretch();
        lyt->addWidget(lbl);

        setLayout(lyt);
    }

    void Label::setText(const QString &text) const {
        lbl->setText(text.isEmpty() ? u"-"_s : text);
    }
}
