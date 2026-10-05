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
#include <QLabel>

#include "../PPage.h"
#include "../../classes/Settings.h"
#include "../../widgets/components/Select/Select.h"
#include "../../widgets/components/Switch/SwitchButton.h"

namespace PWT::UI::PAGE {
    class ClientSettings final: public PPage {
        Q_OBJECT

    private:
        App::Settings &settings = App::Settings::get();
        QHash<QString, GamepadMapping> gamepadMappings;
        int prevGamepadMapIdx = -1;
        Select *defaultDaemon;
        Select *quitBehavior;
        SwitchButton *rememberWindowState;
        SwitchButton *startup;
        Select *theme;
        Select *kbUp;
        Select *kbDown;
        Select *kbLeft;
        Select *kbRight;
        Select *kbFastLeft;
        Select *kbFastRight;
        Select *kbAction;
        Select *kbBack;
        Select *kbScrollUp;
        Select *kbScrollDown;
        Select *kbScrollTop;
        Select *kbScrollBottom;
        Select *kbInputMode;
        Select *kbNavbarUp;
        Select *kbNavbarDown;
        Select *kbRefresh;
        Select *kbApply;
        Select *gamepadMap;
        QLabel *gamepadStatus;
        Select *gpUp;
        Select *gpDown;
        Select *gpLeft;
        Select *gpRight;
        Select *gpFastLeft;
        Select *gpFastRight;
        Select *gpAction;
        Select *gpBack;
        Select *gpScrollUp;
        Select *gpScrollDown;
        Select *gpScrollTop;
        Select *gpScrollBottom;
        Select *gpInputMode;
        Select *gpNavbarUp;
        Select *gpNavbarDown;
        Select *gpRefresh;
        Select *gpApply;
        Select *gpComboSlot1;
        Select *gpComboSlot2;
        Select *gpComboSlot3;

        void loadSettings();
        void setGamepadButtons() const;
        void saveGamepadMapping();

    public:
        ClientSettings();

        void refreshDaemonList() const;

    private slots:
        void onApplyClicked();
        void onGamepadMapChanged(const QString &text);
        void onGamepadMapDeleted();

    public slots:
        void onGamepadAdded(const QString &id) const;
        void onGamepadRemoved(const QString &id) const;
    };
}