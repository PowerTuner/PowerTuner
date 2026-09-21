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

#include "../../components/NavButton/NavButtonSinRotate.h"
#include "../../components/Scrollarea/ScrollArea.h"

namespace PWT::UI {
    class Navbar final: public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *lyt;
        ScrollArea *scrollArea;
        NavButton *active;
        int activeIdx;
        NavButtonSinRotate *refreshBtn;
        NavButton *applyBtn;

        void switchPage(int idx, NavButton *btn);

    public:
        Navbar();

        void switchPageUp();
        void switchPageDown();
        void setIndicator(int idx) const;

    private slots:
        void onNavButtonClicked();
        void onRefreshClicked();
        void onApplyClicked();

    signals:
        void pageChanged(int idx);
        void refreshUI();
        void applyChanges();
    };
}