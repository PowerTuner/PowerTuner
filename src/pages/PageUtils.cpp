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
#include <QLabel>

#include "PageUtils.h"

namespace PWT::UI::PAGE {
    QHBoxLayout *makeHItem(const QString &label, QWidget *widget) {
        QHBoxLayout *hlyt = new QHBoxLayout();

        hlyt->addWidget(new QLabel(label));
        hlyt->addStretch();
        hlyt->addWidget(widget);

        return hlyt;
    }

    QVBoxLayout *makeVItem(const QString &label, QWidget *widget) {
        QVBoxLayout *vlyt = new QVBoxLayout();

        vlyt->addWidget(new QLabel(label));
        vlyt->addWidget(widget);

        return vlyt;
    }
}