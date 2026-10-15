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
#pragma once
#include "../PInputItem.h"
#include "../LineEdit/LineEdit.h"

namespace PWT::UI {
    class SpinBox final: public QWidget, public PInputItem {
        Q_OBJECT

    private:
        LineEdit *editBox = nullptr;
        unsigned long range_min = 0;
        unsigned long range_max = UINT_MAX;

        void clampToRange() const;

    protected:
        void wheelEvent(QWheelEvent *event) override;

    public:
        SpinBox();

        void setRange(unsigned long min, unsigned long max);
        void setValue(unsigned long v) const;
        [[nodiscard]] unsigned long value() const;
        void addToValue() const;
        void subtractFromValue() const;
        void setFocused(bool enable) override;
        void activate(bool gamepad) override;
        void handleButton(ButtonKey key) override;
        void writeVKeyboardText(const QString &text) override;

    private slots:
        void onEditReturnPressed();
        void onEditMouseActivation(PInputItem *);

    signals:
        void mouseActivation(PInputItem *itm);
        void showVKeyboard(const QString &text);
    };
}
