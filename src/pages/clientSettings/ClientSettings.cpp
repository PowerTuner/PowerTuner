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
#include <QMetaEnum>

#include "ClientSettings.h"
#include "../../widgets/pages/Title/Title.h"
#include "../../widgets/components/Button/Button.h"
#include "../../include/keyMap.h"
#include "../PageUtils.h"

namespace PWT::UI::PAGE {
    ClientSettings::ClientSettings() {
        QHBoxLayout *applyBtnLyt = new QHBoxLayout();
        const QMetaEnum styleEnumMeta = QMetaEnum::fromType<Style::StyleType>();
        Button *applyBtn = new Button(u"Apply"_s);

        defaultDaemon = new Select();
        quitBehavior = new Select();
        rememberWindowState = new SwitchButton();
        startup = new SwitchButton();
        theme = new Select();
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

        refreshDaemonList();
        quitBehavior->addItems({u"Quit"_s, u"Tray"_s});

        for (int i=0,l=styleEnumMeta.keyCount(); i<l; ++i)
            theme->addItem(styleEnumMeta.key(i), styleEnumMeta.value(i));

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
        lyt->addLayout(makeHItem(u"Default daemon"_s, defaultDaemon));
        lyt->addLayout(makeHItem(u"Quit behavior"_s, quitBehavior));
        lyt->addLayout(makeHItem(u"Remember window state"_s, rememberWindowState));
        lyt->addLayout(makeHItem(u"Run at startup"_s, startup));
        lyt->addLayout(makeHItem(u"Theme"_s, theme));
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

        QObject::connect(applyBtn, &Button::clicked, this, &ClientSettings::onApplyClicked);
    }

    void ClientSettings::refresh() const {
        defaultDaemon->setCurrentIndex(settings.getDefaultDaemon());
        quitBehavior->setCurrentIndex(settings.getCloseToTray());
        rememberWindowState->setChecked(settings.getRememberWindowState());
        startup->setChecked(settings.getRunAtStartup());
        theme->setCurrentIndex(theme->findData(static_cast<int>(settings.getTheme())));
        kbMapUp->setCurrentIndex(kbMapUp->findData(settings.getKeyboardUp()));
        kbMapDown->setCurrentIndex(kbMapDown->findData(settings.getKeyboardDown()));
        kbMapLeft->setCurrentIndex(kbMapLeft->findData(settings.getKeyboardLeft()));
        kbMapRight->setCurrentIndex(kbMapRight->findData(settings.getKeyboardRight()));
        kbMapFastLeft->setCurrentIndex(kbMapFastLeft->findData(settings.getKeyboardFastLeft()));
        kbMapFastRight->setCurrentIndex(kbMapFastRight->findData(settings.getKeyboardFastRight()));
        kbMapAction->setCurrentIndex(kbMapAction->findData(settings.getKeyboardAction()));
        kbMapBack->setCurrentIndex(kbMapBack->findData(settings.getKeyboardBack()));
        kbMapScrollUp->setCurrentIndex(kbMapScrollUp->findData(settings.getKeyboardScrollUp()));
        kbMapScrollDown->setCurrentIndex(kbMapScrollDown->findData(settings.getKeyboardScrollDown()));
        kbMapScrollTop->setCurrentIndex(kbMapScrollTop->findData(settings.getKeyboardScrollTop()));
        kbMapScrollBottom->setCurrentIndex(kbMapScrollBottom->findData(settings.getKeyboardScrollBottom()));
        kbMapInputMode->setCurrentIndex(kbMapInputMode->findData(settings.getKeyboardInputMode()));
        kbNavbarUp->setCurrentIndex(kbNavbarUp->findData(settings.getKeyboardNavbarUp()));
        kbNavbarDown->setCurrentIndex(kbNavbarDown->findData(settings.getKeyboardNavbarDown()));
        kbMapRefresh->setCurrentIndex(kbMapRefresh->findData(settings.getKeyboardRefresh()));
        kbMapApply->setCurrentIndex(kbMapApply->findData(settings.getKeyboardApply()));
    }

    void ClientSettings::refreshDaemonList() const {
        defaultDaemon->clear();

        for (const Daemon &d: settings.getDaemonList())
            defaultDaemon->addItem(d.name);
    }

    void ClientSettings::onApplyClicked() {
        settings.setDefaultDaemon(defaultDaemon->currentIndex());
        settings.setCloseToTray(quitBehavior->currentIndex());
        settings.setRememberWindowState(rememberWindowState->isChecked());
        settings.setRunAtStartup(startup->isChecked());
        settings.setTheme(static_cast<Style::StyleType>(theme->currentData().toInt()));
        settings.setKeyboardUp(static_cast<Qt::Key>(kbMapUp->currentData().toInt()));
        settings.setKeyboardDown(static_cast<Qt::Key>(kbMapDown->currentData().toInt()));
        settings.setKeyboardLeft(static_cast<Qt::Key>(kbMapLeft->currentData().toInt()));
        settings.setKeyboardRight(static_cast<Qt::Key>(kbMapRight->currentData().toInt()));
        settings.setKeyboardFastLeft(static_cast<Qt::Key>(kbMapFastLeft->currentData().toInt()));
        settings.setKeyboardFastRight(static_cast<Qt::Key>(kbMapFastRight->currentData().toInt()));
        settings.setKeyboardAction(static_cast<Qt::Key>(kbMapAction->currentData().toInt()));
        settings.setKeyboardBack(static_cast<Qt::Key>(kbMapBack->currentData().toInt()));
        settings.setKeyboardScrollUp(static_cast<Qt::Key>(kbMapScrollUp->currentData().toInt()));
        settings.setKeyboardScrollDown(static_cast<Qt::Key>(kbMapScrollDown->currentData().toInt()));
        settings.setKeyboardScrollTop(static_cast<Qt::Key>(kbMapScrollTop->currentData().toInt()));
        settings.setKeyboardScrollBottom(static_cast<Qt::Key>(kbMapScrollBottom->currentData().toInt()));
        settings.setKeyboardInputMode(static_cast<Qt::Key>(kbMapInputMode->currentData().toInt()));
        settings.setKeyboardNavbarUp(static_cast<Qt::Key>(kbNavbarUp->currentData().toInt()));
        settings.setKeyboardNavbarDown(static_cast<Qt::Key>(kbNavbarDown->currentData().toInt()));
        settings.setKeyboardRefresh(static_cast<Qt::Key>(kbMapRefresh->currentData().toInt()));
        settings.setKeyboardApply(static_cast<Qt::Key>(kbMapApply->currentData().toInt()));

        if (!settings.save())
            emit logSent(u"failed to write settings to disk"_s);
        else
            emit logSent(u"settings saved successfully"_s);
    }
}
