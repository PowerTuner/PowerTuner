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
#include <QVBoxLayout>

#include "../widgets/components/PInputItem.h"
#include "../widgets/components/Scrollarea/ScrollArea.h"

namespace PWT::UI::PAGE {
    class PPage: public QWidget {
        Q_OBJECT

    private:
        ScrollArea *scrollArea = nullptr;
        QVector<std::pair<QWidget *, PInputItem *>> inputList;
        int focusedIdx = -1;

        [[nodiscard]] bool isValidFocusIndex() const;
        [[nodiscard]] bool tryFocusComponent(int idx);
        void focusLastWidget();
        void focusPrevNextViewportWidget(bool next);

    protected:
        QVBoxLayout *lyt = nullptr;

        void collectPageInputs(const QLayout *layout);
        void focusFirstWidget();

    public:
        PPage();

        virtual void handleButton(ButtonKey key, bool gamepad);
    };
}