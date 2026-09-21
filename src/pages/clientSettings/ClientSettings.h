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
#include "../PPage.h"
#include "../../classes/Settings.h"
#include "../../widgets/components/Select/Select.h"
#include "../../widgets/components/Switch/SwitchButton.h"
#include "../../widgets/components/Button/Button.h"

namespace PWT::UI::PAGE {
    class ClientSettings final: public PPage {
        Q_OBJECT

    private:
        App::Settings &settings = App::Settings::get();
        Select *defaultDaemon;
        Select *quitBehavior;
        SwitchButton *rememberWindowState;
        SwitchButton *startup;
        Select *theme;
        Select *kbMapUp;
        Select *kbMapDown;
        Select *kbMapLeft;
        Select *kbMapRight;
        Select *kbMapFastLeft;
        Select *kbMapFastRight;
        Select *kbMapAction;
        Select *kbMapBack;
        Select *kbMapScrollUp;
        Select *kbMapScrollDown;
        Select *kbMapScrollTop;
        Select *kbMapScrollBottom;
        Select *kbMapInputMode;
        Select *kbNavbarUp;
        Select *kbNavbarDown;
        Select *kbMapRefresh;
        Select *kbMapApply;
        Button *applyBtn;

    public:
        ClientSettings();

        void refresh() const;

    private slots:
        void onApplyClicked();

    signals:
        void logSent(const QString &msg);
    };
}