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
        kbUp = new Select();
        kbDown = new Select();
        kbLeft = new Select();
        kbRight = new Select();
        kbFastLeft = new Select();
        kbFastRight = new Select();
        kbAction = new Select();
        kbBack = new Select();
        kbScrollUp = new Select();
        kbScrollDown = new Select();
        kbScrollTop = new Select();
        kbScrollBottom = new Select();
        kbInputMode = new Select();
        kbNavbarUp = new Select();
        kbNavbarDown = new Select();
        kbRefresh = new Select();
        kbApply = new Select();

        for (int i=0,l=styleEnumMeta.keyCount(); i<l; ++i)
            theme->addItem(styleEnumMeta.key(i), styleEnumMeta.value(i));

        for (const auto &[key, ascii]: KeyMap.asKeyValueRange()) {
            kbUp->addItem(ascii, key);
            kbDown->addItem(ascii, key);
            kbLeft->addItem(ascii, key);
            kbRight->addItem(ascii, key);
            kbFastLeft->addItem(ascii, key);
            kbFastRight->addItem(ascii, key);
            kbAction->addItem(ascii, key);
            kbBack->addItem(ascii, key);
            kbScrollUp->addItem(ascii, key);
            kbScrollDown->addItem(ascii, key);
            kbScrollTop->addItem(ascii, key);
            kbScrollBottom->addItem(ascii, key);
            kbInputMode->addItem(ascii, key);
            kbNavbarUp->addItem(ascii, key);
            kbNavbarDown->addItem(ascii, key);
            kbRefresh->addItem(ascii, key);
            kbApply->addItem(ascii, key);
        }

        quitBehavior->addItems({u"Quit"_s, u"Tray"_s});
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
        lyt->addLayout(makeHItem(u"Up"_s, kbUp));
        lyt->addLayout(makeHItem(u"Down"_s, kbDown));
        lyt->addLayout(makeHItem(u"Left"_s, kbLeft));
        lyt->addLayout(makeHItem(u"Right"_s, kbRight));
        lyt->addLayout(makeHItem(u"Fast Left"_s, kbFastLeft));
        lyt->addLayout(makeHItem(u"Fast Right"_s, kbFastRight));
        lyt->addLayout(makeHItem(u"Action"_s, kbAction));
        lyt->addLayout(makeHItem(u"Back"_s, kbBack));
        lyt->addLayout(makeHItem(u"Scroll Up"_s, kbScrollUp));
        lyt->addLayout(makeHItem(u"Scroll Down"_s, kbScrollDown));
        lyt->addLayout(makeHItem(u"Scroll Top"_s, kbScrollTop));
        lyt->addLayout(makeHItem(u"Scroll Bottom"_s, kbScrollBottom));
        lyt->addLayout(makeHItem(u"Input Mode"_s, kbInputMode));
        lyt->addLayout(makeHItem(u"Navbar Up"_s, kbNavbarUp));
        lyt->addLayout(makeHItem(u"Navbar Down"_s, kbNavbarDown));
        lyt->addLayout(makeHItem(u"Refresh"_s, kbRefresh));
        lyt->addLayout(makeHItem(u"Apply"_s, kbApply));
        lyt->addStretch();
        lyt->addSpacing(12);
        lyt->addLayout(applyBtnLyt);

        setFocusPolicy(Qt::NoFocus);
        loadSettings();
        collectPageInputs(lyt);
        focusFirstWidget();

        QObject::connect(applyBtn, &Button::clicked, this, &ClientSettings::onApplyClicked);
    }

    void ClientSettings::loadSettings() {
        refreshDaemonList();
        quitBehavior->setCurrentIndex(settings.getCloseToTray());
        rememberWindowState->setChecked(settings.getRememberWindowState());
        startup->setChecked(settings.getRunAtStartup());
        theme->setCurrentIndex(theme->findData(static_cast<int>(settings.getTheme())));
        kbUp->setCurrentIndex(kbUp->findData(settings.getKeyboardUp()));
        kbDown->setCurrentIndex(kbDown->findData(settings.getKeyboardDown()));
        kbLeft->setCurrentIndex(kbLeft->findData(settings.getKeyboardLeft()));
        kbRight->setCurrentIndex(kbRight->findData(settings.getKeyboardRight()));
        kbFastLeft->setCurrentIndex(kbFastLeft->findData(settings.getKeyboardFastLeft()));
        kbFastRight->setCurrentIndex(kbFastRight->findData(settings.getKeyboardFastRight()));
        kbAction->setCurrentIndex(kbAction->findData(settings.getKeyboardAction()));
        kbBack->setCurrentIndex(kbBack->findData(settings.getKeyboardBack()));
        kbScrollUp->setCurrentIndex(kbScrollUp->findData(settings.getKeyboardScrollUp()));
        kbScrollDown->setCurrentIndex(kbScrollDown->findData(settings.getKeyboardScrollDown()));
        kbScrollTop->setCurrentIndex(kbScrollTop->findData(settings.getKeyboardScrollTop()));
        kbScrollBottom->setCurrentIndex(kbScrollBottom->findData(settings.getKeyboardScrollBottom()));
        kbInputMode->setCurrentIndex(kbInputMode->findData(settings.getKeyboardInputMode()));
        kbNavbarUp->setCurrentIndex(kbNavbarUp->findData(settings.getKeyboardNavbarUp()));
        kbNavbarDown->setCurrentIndex(kbNavbarDown->findData(settings.getKeyboardNavbarDown()));
        kbRefresh->setCurrentIndex(kbRefresh->findData(settings.getKeyboardRefresh()));
        kbApply->setCurrentIndex(kbApply->findData(settings.getKeyboardApply()));
    }

    void ClientSettings::refreshDaemonList() const {
        defaultDaemon->clear();

        for (const Daemon &d: settings.getDaemonList())
            defaultDaemon->addItem(d.name);

        defaultDaemon->setCurrentIndex(settings.getDefaultDaemon());
    }

    void ClientSettings::onApplyClicked() {
        settings.setDefaultDaemon(defaultDaemon->currentIndex());
        settings.setCloseToTray(quitBehavior->currentIndex());
        settings.setRememberWindowState(rememberWindowState->isChecked());
        settings.setRunAtStartup(startup->isChecked());
        settings.setTheme(static_cast<Style::StyleType>(theme->currentData().toInt()));
        settings.setKeyboardUp(static_cast<Qt::Key>(kbUp->currentData().toInt()));
        settings.setKeyboardDown(static_cast<Qt::Key>(kbDown->currentData().toInt()));
        settings.setKeyboardLeft(static_cast<Qt::Key>(kbLeft->currentData().toInt()));
        settings.setKeyboardRight(static_cast<Qt::Key>(kbRight->currentData().toInt()));
        settings.setKeyboardFastLeft(static_cast<Qt::Key>(kbFastLeft->currentData().toInt()));
        settings.setKeyboardFastRight(static_cast<Qt::Key>(kbFastRight->currentData().toInt()));
        settings.setKeyboardAction(static_cast<Qt::Key>(kbAction->currentData().toInt()));
        settings.setKeyboardBack(static_cast<Qt::Key>(kbBack->currentData().toInt()));
        settings.setKeyboardScrollUp(static_cast<Qt::Key>(kbScrollUp->currentData().toInt()));
        settings.setKeyboardScrollDown(static_cast<Qt::Key>(kbScrollDown->currentData().toInt()));
        settings.setKeyboardScrollTop(static_cast<Qt::Key>(kbScrollTop->currentData().toInt()));
        settings.setKeyboardScrollBottom(static_cast<Qt::Key>(kbScrollBottom->currentData().toInt()));
        settings.setKeyboardInputMode(static_cast<Qt::Key>(kbInputMode->currentData().toInt()));
        settings.setKeyboardNavbarUp(static_cast<Qt::Key>(kbNavbarUp->currentData().toInt()));
        settings.setKeyboardNavbarDown(static_cast<Qt::Key>(kbNavbarDown->currentData().toInt()));
        settings.setKeyboardRefresh(static_cast<Qt::Key>(kbRefresh->currentData().toInt()));
        settings.setKeyboardApply(static_cast<Qt::Key>(kbApply->currentData().toInt()));

        if (!settings.save())
            emit logSent(u"failed to write settings to disk"_s);
        else
            emit logSent(u"settings saved successfully"_s);
    }
}
