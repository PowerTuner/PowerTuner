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
#include "ClientSettings.h"
#include "../../widgets/pages/Title/Title.h"
#include "../../include/keyMap.h"
#include "../PageUtils.h"

namespace PWT::UI::PAGE {
    ClientSettings::ClientSettings() {
        QHBoxLayout *applyBtnLyt = new QHBoxLayout();

        daemon = new Select();
        quitBehavior = new Select();
        rememberWindowState = new SwitchButton();
        startup = new SwitchButton();
        kbMapUp = new Select();
        kbMapDown = new Select();
        kbMapLeft = new Select();
        kbMapRight = new Select();
        kbMapFastLeft = new Select();
        kbMapFastRight = new Select();
        kbMapAction = new Select();
        kbMapBack = new Select();
        kbMapScrollUp = new Select();
        kbMapScrollDown = new Select();
        kbMapScrollTop = new Select();
        kbMapScrollBottom = new Select();
        kbMapInputMode = new Select();
        kbNavbarUp = new Select();
        kbNavbarDown = new Select();
        kbMapRefresh = new Select();
        kbMapApply = new Select();
        applyBtn = new Button(u"Apply"_s);

        daemon->addItem(u"---"_s);
        quitBehavior->addItems({u"Quit"_s, u"Tray"_s});

        for (const auto &[key, ascii]: KeyMap.asKeyValueRange()) {
            kbMapUp->addItem(ascii, key);
            kbMapDown->addItem(ascii, key);
            kbMapLeft->addItem(ascii, key);
            kbMapRight->addItem(ascii, key);
            kbMapFastLeft->addItem(ascii, key);
            kbMapFastRight->addItem(ascii, key);
            kbMapAction->addItem(ascii, key);
            kbMapBack->addItem(ascii, key);
            kbMapScrollUp->addItem(ascii, key);
            kbMapScrollDown->addItem(ascii, key);
            kbMapScrollTop->addItem(ascii, key);
            kbMapScrollBottom->addItem(ascii, key);
            kbMapInputMode->addItem(ascii, key);
            kbNavbarUp->addItem(ascii, key);
            kbNavbarDown->addItem(ascii, key);
            kbMapRefresh->addItem(ascii, key);
            kbMapApply->addItem(ascii, key);
        }

        applyBtnLyt->addStretch();
        applyBtnLyt->addWidget(applyBtn);
        lyt->setSpacing(12);
        lyt->addWidget(new Title(u"\uf2d0 Application"_s));
        lyt->addLayout(makeHItem(u"Daemon"_s, daemon));
        lyt->addLayout(makeHItem(u"Quit behavior"_s, quitBehavior));
        lyt->addLayout(makeHItem(u"Remember window state"_s, rememberWindowState));
        lyt->addLayout(makeHItem(u"Run at startup"_s, startup));
        lyt->addSpacing(6);
        lyt->addWidget(new Title(u"\uf11c Keyboard mapping"_s));
        lyt->addLayout(makeHItem(u"Up"_s, kbMapUp));
        lyt->addLayout(makeHItem(u"Down"_s, kbMapDown));
        lyt->addLayout(makeHItem(u"Left"_s, kbMapLeft));
        lyt->addLayout(makeHItem(u"Right"_s, kbMapRight));
        lyt->addLayout(makeHItem(u"Fast Left"_s, kbMapFastLeft));
        lyt->addLayout(makeHItem(u"Fast Right"_s, kbMapFastRight));
        lyt->addLayout(makeHItem(u"Action"_s, kbMapAction));
        lyt->addLayout(makeHItem(u"Back"_s, kbMapBack));
        lyt->addLayout(makeHItem(u"Scroll Up"_s, kbMapScrollUp));
        lyt->addLayout(makeHItem(u"Scroll Down"_s, kbMapScrollDown));
        lyt->addLayout(makeHItem(u"Scroll Top"_s, kbMapScrollTop));
        lyt->addLayout(makeHItem(u"Scroll Bottom"_s, kbMapScrollBottom));
        lyt->addLayout(makeHItem(u"Input Mode"_s, kbMapInputMode));
        lyt->addLayout(makeHItem(u"Navbar Up"_s, kbNavbarUp));
        lyt->addLayout(makeHItem(u"Navbar Down"_s, kbNavbarDown));
        lyt->addLayout(makeHItem(u"Refresh"_s, kbMapRefresh));
        lyt->addLayout(makeHItem(u"Apply"_s, kbMapApply));
        lyt->addStretch();
        lyt->addSpacing(12);
        lyt->addLayout(applyBtnLyt);

        setFocusPolicy(Qt::NoFocus);
        collectPageInputs(lyt);
        focusFirstWidget();
    }
}
