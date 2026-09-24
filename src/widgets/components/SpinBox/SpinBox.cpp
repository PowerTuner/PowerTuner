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

    SpinBox::SpinBox(): PInputItem(this) {
        QHBoxLayout *lyt = new QHBoxLayout();
        QVBoxLayout *btnLyt = new QVBoxLayout();
        Button *plus = new Button(u"+"_s, false);
        Button *minus = new Button(u"-"_s, false);

        editBox = new LineEdit();

        editBox->setValidator(new QRegularExpressionValidator(QRegularExpression(R"([0-9]+)"), this));
        plus->setFixedSize(26, 22);
        minus->setFixedSize(26, 22);
        setFocusPolicy(Qt::NoFocus);

        btnLyt->setContentsMargins(0, 0, 0, 0);
        btnLyt->setSpacing(0);
        btnLyt->addWidget(plus);
        btnLyt->addWidget(minus);
        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->setSpacing(0);
        lyt->addWidget(editBox);
        lyt->addLayout(btnLyt);

        setLayout(lyt);

        QObject::connect(editBox, &LineEdit::returnPressed, this, &SpinBox::onEditReturnPressed);
        QObject::connect(editBox, &LineEdit::mouseActivation, this, &SpinBox::onEditMouseActivation);
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

    void SpinBox::clampToRange() const {
        if (editBox->text().isEmpty())
            return;

        bool res;
        const unsigned long v = editBox->text().toULong(&res);

        if (res)
            editBox->setText(QString::number(std::clamp(v, range_min, range_max)));
        else
            editBox->setText("");
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

        range_min = min;
        range_max = max;
    }

    void SpinBox::setValue(const unsigned long v) const {
        editBox->setText(QString::number(std::clamp(v, range_min, range_max)));
    }

    unsigned long SpinBox::value() const {
        bool res;
        const unsigned long v = editBox->text().toULong(&res);

        if (!res)
            return range_min;

        return std::clamp(v, range_min, range_max);
    }

    void SpinBox::setFocused(const bool enable) {
        editBox->setFocused(enable);
    }

    void SpinBox::activate() {
        isActive = true;
        editBox->activate();
    }

    void SpinBox::handleButton(const ButtonKey key) {
        switch (key) {
            case ButtonKey::Up: {
                onPlusClicked();
            }
                break;
            case ButtonKey::Down: {
                onMinusClicked();
            }
                break;
            case ButtonKey::Back: {
                clampToRange();
                isActive = false;
                editBox->handleButton(key);
            }
                break;
            default:
                break;
        }
    }

    void SpinBox::onPlusClicked() const {
        if (editBox->text().isEmpty())
            return editBox->setText(QString::number(range_min));

        bool res;
        unsigned long v = editBox->text().toULong(&res);

        if (res)
            editBox->setText(QString::number(std::clamp(++v, range_min, range_max)));
    }

    void SpinBox::onMinusClicked() const {
        if (editBox->text().isEmpty())
            return editBox->setText(QString::number(range_min));

        bool res;
        unsigned long v = editBox->text().toULong(&res);

        if (res)
            editBox->setText(QString::number(std::clamp(--v, range_min, range_max)));
    }

    void SpinBox::onEditReturnPressed() {
        clampToRange();
        isActive = false;
    }

    void SpinBox::onEditMouseActivation(PInputItem *) {
        emit mouseActivation(this);
    }
}
