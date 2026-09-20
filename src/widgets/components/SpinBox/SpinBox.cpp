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
#include <QVBoxLayout>
#include <QRegularExpressionValidator>
#include <QWheelEvent>

#include "SpinBox.h"
#include "../Button/Button.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    SpinBox::SpinBox() {
        QHBoxLayout *lyt = new QHBoxLayout();
        QVBoxLayout *btnLyt = new QVBoxLayout();
        Button *plus = new Button(u"+"_s, false);
        Button *minus = new Button(u"-"_s, false);

        editBox = new LineEdit();

        editBox->setValidator(new QRegularExpressionValidator(QRegularExpression(R"([0-9]+)"), this));
        plus->setFixedSize(26, 18);
        minus->setFixedSize(26, 18);
        setFocusPolicy(Qt::NoFocus);

        btnLyt->setSpacing(0);
        btnLyt->addStretch();
        btnLyt->addWidget(plus);
        btnLyt->addWidget(minus);
        btnLyt->addStretch();
        lyt->addStretch();
        lyt->setSpacing(0);
        lyt->addWidget(editBox);
        lyt->addLayout(btnLyt);
        lyt->addStretch();

        setLayout(lyt);

        QObject::connect(plus, &Button::clicked, this, &SpinBox::onPlusClicked);
        QObject::connect(minus, &Button::clicked, this, &SpinBox::onMinusClicked);
    }

    void SpinBox::wheelEvent(QWheelEvent *event) {
        const int y = event->angleDelta().y();

        if (y > 0)
            onPlusClicked();
        else if (y < 0)
            onMinusClicked();
        else
            return event->ignore();

        event->accept();
    }

    void SpinBox::setRange(const unsigned long min, const unsigned long max) {
        if (min > max)
            return;

        if (!editBox->text().isEmpty()) {
            bool res;
            const unsigned long v = editBox->text().toULong(&res);

            if (!res)
                editBox->setText(QString::number(min));
            else
                editBox->setText(QString::number(std::clamp(v, min, max)));
        }

        rmin = min;
        rmax = max;
    }

    void SpinBox::onPlusClicked() const {
        if (editBox->text().isEmpty())
            return editBox->setText(QString::number(rmin));

        bool res;
        unsigned long v = editBox->text().toULong(&res);

        if (!res || v == rmax)
            return;
        else if (v > rmax)
            return editBox->setText(QString::number(rmin));

        editBox->setText(QString::number(++v));
    }

    void SpinBox::onMinusClicked() const {
        if (editBox->text().isEmpty())
            return editBox->setText(QString::number(rmin));

        bool res;
        unsigned long v = editBox->text().toULong(&res);

        if (!res || v == rmin)
            return;
        else if (v < rmin)
            return editBox->setText(QString::number(rmin));

        editBox->setText(QString::number(--v));
    }

    void SpinBox::setValue(const unsigned long v) const {
        editBox->setText(QString::number(std::clamp(v, rmin, rmax)));
    }

    unsigned long SpinBox::value() const {
        bool res;
        const unsigned long v = editBox->text().toULong(&res);

        if (!res)
            return rmin;

        return std::clamp(v, rmin, rmax);
    }
}
