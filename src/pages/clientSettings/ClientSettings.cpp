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
#include "../../widgets/components/Button/Button.h"
#include "../../include/keyMap.h"
#include "../../include/GamepadButtonMap.h"
#include "../PageUtils.h"

namespace PWT::UI::PAGE {
    ClientSettings::ClientSettings() {
        QHBoxLayout *applyBtnLyt = new QHBoxLayout();
        QHBoxLayout *gamepadSelLyt = new QHBoxLayout();
        QHBoxLayout *reloadSdlDbLyt = new QHBoxLayout();
        const QMetaEnum styleEnumMeta = QMetaEnum::fromType<Style::StyleType>();
        Button *delGamepadMap = new Button(u"\uf1f8"_s);
        Button *reloadSdlDb = new Button(u"Reload SDL database"_s);
        Button *applyBtn = new Button(u"Apply"_s);
        QFont iconFont = font();

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
        gamepadMap = new Select();
        gamepadStatus = new QLabel();
        gpUp = new Select();
        gpDown = new Select();
        gpLeft = new Select();
        gpRight = new Select();
        gpFastLeft = new Select();
        gpFastRight = new Select();
        gpAction = new Select();
        gpBack = new Select();
        gpScrollUp = new Select();
        gpScrollDown = new Select();
        gpScrollTop = new Select();
        gpScrollBottom = new Select();
        gpInputMode = new Select();
        gpNavbarUp = new Select();
        gpNavbarDown = new Select();
        gpRefresh = new Select();
        gpApply = new Select();
        gpComboSlot1 = new Select();
        gpComboSlot2 = new Select();
        gpComboSlot3 = new Select();

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

        for (const auto &[button, label]: GamepadButtonMap.asKeyValueRange()) {
            gpUp->addItem(label, static_cast<int>(button));
            gpDown->addItem(label, static_cast<int>(button));
            gpLeft->addItem(label, static_cast<int>(button));
            gpRight->addItem(label, static_cast<int>(button));
            gpFastLeft->addItem(label, static_cast<int>(button));
            gpFastRight->addItem(label, static_cast<int>(button));
            gpAction->addItem(label, static_cast<int>(button));
            gpBack->addItem(label, static_cast<int>(button));
            gpScrollUp->addItem(label, static_cast<int>(button));
            gpScrollDown->addItem(label, static_cast<int>(button));
            gpScrollTop->addItem(label, static_cast<int>(button));
            gpScrollBottom->addItem(label, static_cast<int>(button));
            gpInputMode->addItem(label, static_cast<int>(button));
            gpNavbarUp->addItem(label, static_cast<int>(button));
            gpNavbarDown->addItem(label, static_cast<int>(button));
            gpRefresh->addItem(label, static_cast<int>(button));
            gpApply->addItem(label, static_cast<int>(button));
        }

        for (const auto &[button, label]: GamepadButtonComboMap.asKeyValueRange()) {
            gpComboSlot1->addItem(label, static_cast<int>(button));
            gpComboSlot2->addItem(label, static_cast<int>(button));
            gpComboSlot3->addItem(label, static_cast<int>(button));
        }

        iconFont.setFamily(u"Font Awesome 7 Free"_s);
        quitBehavior->addItems({u"Quit"_s, u"Tray"_s});
        gamepadStatus->setFont(iconFont);
        delGamepadMap->setFixedWidth(50);

        gamepadSelLyt->addWidget(gamepadMap);
        gamepadSelLyt->addWidget(gamepadStatus);
        gamepadSelLyt->addStretch();
        gamepadSelLyt->addWidget(delGamepadMap);
        reloadSdlDbLyt->addStretch();
        reloadSdlDbLyt->addWidget(reloadSdlDb);
        applyBtnLyt->addStretch();
        applyBtnLyt->addWidget(applyBtn);
        lyt->setSpacing(12);
        lyt->addLayout(makeTitle(u"Application"_s, u"\uf2d0"_s));
        lyt->addLayout(makeHItem(u"Default daemon"_s, defaultDaemon));
        lyt->addLayout(makeHItem(u"Quit behavior"_s, quitBehavior));
        lyt->addLayout(makeHItem(u"Remember window state"_s, rememberWindowState));
        lyt->addLayout(makeHItem(u"Run at startup"_s, startup));
        lyt->addLayout(makeHItem(u"Theme"_s, theme));
        lyt->addSpacing(6);
        lyt->addLayout(makeTitle(u"Keyboard mapping"_s, u"\uf11c"_s));
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
        lyt->addSpacing(6);
        lyt->addLayout(makeTitle(u"Gamepad mapping"_s, u"\uf11b"_s));
        lyt->addLayout(gamepadSelLyt);
        lyt->addSpacing(12);
        lyt->addLayout(makeHItem(u"Up"_s, gpUp));
        lyt->addLayout(makeHItem(u"Down"_s, gpDown));
        lyt->addLayout(makeHItem(u"Left"_s, gpLeft));
        lyt->addLayout(makeHItem(u"Right"_s, gpRight));
        lyt->addLayout(makeHItem(u"Fast Left"_s, gpFastLeft));
        lyt->addLayout(makeHItem(u"Fast Right"_s, gpFastRight));
        lyt->addLayout(makeHItem(u"Action"_s, gpAction));
        lyt->addLayout(makeHItem(u"Back"_s, gpBack));
        lyt->addLayout(makeHItem(u"Scroll Up"_s, gpScrollUp));
        lyt->addLayout(makeHItem(u"Scroll Down"_s, gpScrollDown));
        lyt->addLayout(makeHItem(u"Scroll Top"_s, gpScrollTop));
        lyt->addLayout(makeHItem(u"Scroll Bottom"_s, gpScrollBottom));
        lyt->addLayout(makeHItem(u"Input Mode"_s, gpInputMode));
        lyt->addLayout(makeHItem(u"Navbar Up"_s, gpNavbarUp));
        lyt->addLayout(makeHItem(u"Navbar Down"_s, gpNavbarDown));
        lyt->addLayout(makeHItem(u"Refresh"_s, gpRefresh));
        lyt->addLayout(makeHItem(u"Apply"_s, gpApply));
        lyt->addLayout(makeHItem(u"Application shortcut key 1"_s, gpComboSlot1));
        lyt->addLayout(makeHItem(u"Application shortcut key 2"_s, gpComboSlot2));
        lyt->addLayout(makeHItem(u"Application shortcut key 3"_s, gpComboSlot3));
        lyt->addLayout(reloadSdlDbLyt);
        lyt->addStretch();
        lyt->addSpacing(20);
        lyt->addLayout(applyBtnLyt);

        setFocusPolicy(Qt::NoFocus);
        loadSettings();
        collectPageInputs(lyt);
        focusFirstWidget();

        QObject::connect(gamepadMap, &Select::currentTextChanged, this, &ClientSettings::onGamepadMapChanged);
        QObject::connect(delGamepadMap, &Button::clicked, this, &ClientSettings::onGamepadMapDeleted);
        QObject::connect(reloadSdlDb, &Button::clicked, this, &ClientSettings::reloadSDLDB);
        QObject::connect(applyBtn, &Button::clicked, this, &ClientSettings::onApplyClicked);
    }

    void ClientSettings::loadSettings() {
        gamepadMappings = settings.getGamepadMappings();

        for (const auto &[id, map]: gamepadMappings.asKeyValueRange())
            gamepadMap->addItem(id);

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
        onGamepadMapChanged(gamepadMap->currentText());
    }

    void ClientSettings::setGamepadButtons() const {
        const GamepadMapping map = gamepadMappings.value(gamepadMap->currentText(), GamepadMapping());

        gpUp->setCurrentIndex(gpUp->findData(static_cast<int>(map.up)));
        gpDown->setCurrentIndex(gpDown->findData(static_cast<int>(map.down)));
        gpLeft->setCurrentIndex(gpLeft->findData(static_cast<int>(map.left)));
        gpRight->setCurrentIndex(gpRight->findData(static_cast<int>(map.right)));
        gpFastLeft->setCurrentIndex(gpFastLeft->findData(static_cast<int>(map.fastLeft)));
        gpFastRight->setCurrentIndex(gpFastRight->findData(static_cast<int>(map.fastRight)));
        gpAction->setCurrentIndex(gpAction->findData(static_cast<int>(map.action)));
        gpBack->setCurrentIndex(gpBack->findData(static_cast<int>(map.back)));
        gpScrollUp->setCurrentIndex(gpScrollUp->findData(static_cast<int>(map.scrollUp)));
        gpScrollDown->setCurrentIndex(gpScrollDown->findData(static_cast<int>(map.scrollDown)));
        gpScrollTop->setCurrentIndex(gpScrollTop->findData(static_cast<int>(map.scrollTop)));
        gpScrollBottom->setCurrentIndex(gpScrollBottom->findData(static_cast<int>(map.scrollBottom)));
        gpInputMode->setCurrentIndex(gpInputMode->findData(static_cast<int>(map.inputMode)));
        gpNavbarUp->setCurrentIndex(gpNavbarUp->findData(static_cast<int>(map.navbarUp)));
        gpNavbarDown->setCurrentIndex(gpNavbarDown->findData(static_cast<int>(map.navbarDown)));
        gpRefresh->setCurrentIndex(gpRefresh->findData(static_cast<int>(map.refresh)));
        gpApply->setCurrentIndex(gpApply->findData(static_cast<int>(map.apply)));
        gpComboSlot1->setCurrentIndex(gpComboSlot1->findData(static_cast<int>(map.appComboSlot1)));
        gpComboSlot2->setCurrentIndex(gpComboSlot2->findData(static_cast<int>(map.appComboSlot2)));
        gpComboSlot3->setCurrentIndex(gpComboSlot3->findData(static_cast<int>(map.appComboSlot3)));
    }

    void ClientSettings::saveGamepadMapping() {
        const QString id = gamepadMap->itemText(prevGamepadMapIdx);

        if (id.isEmpty())
            return;

        const GamepadMapping map = {
            .navbarUp = static_cast<GamepadButton>(gpNavbarUp->currentData().toInt()),
            .navbarDown = static_cast<GamepadButton>(gpNavbarDown->currentData().toInt()),
            .refresh = static_cast<GamepadButton>(gpRefresh->currentData().toInt()),
            .apply = static_cast<GamepadButton>(gpApply->currentData().toInt()),
            .up = static_cast<GamepadButton>(gpUp->currentData().toInt()),
            .down = static_cast<GamepadButton>(gpDown->currentData().toInt()),
            .left = static_cast<GamepadButton>(gpLeft->currentData().toInt()),
            .right = static_cast<GamepadButton>(gpRight->currentData().toInt()),
            .fastLeft = static_cast<GamepadButton>(gpFastLeft->currentData().toInt()),
            .fastRight = static_cast<GamepadButton>(gpFastRight->currentData().toInt()),
            .action = static_cast<GamepadButton>(gpAction->currentData().toInt()),
            .back = static_cast<GamepadButton>(gpBack->currentData().toInt()),
            .scrollUp = static_cast<GamepadButton>(gpScrollUp->currentData().toInt()),
            .scrollDown = static_cast<GamepadButton>(gpScrollDown->currentData().toInt()),
            .scrollTop = static_cast<GamepadButton>(gpScrollTop->currentData().toInt()),
            .scrollBottom = static_cast<GamepadButton>(gpScrollBottom->currentData().toInt()),
            .inputMode = static_cast<GamepadButton>(gpInputMode->currentData().toInt()),
            .appComboSlot1 = static_cast<GamepadButton>(gpComboSlot1->currentData().toInt()),
            .appComboSlot2 = static_cast<GamepadButton>(gpComboSlot2->currentData().toInt()),
            .appComboSlot3 = static_cast<GamepadButton>(gpComboSlot3->currentData().toInt())
        };

        gamepadMappings.insert_or_assign(id, map);
    }

    void ClientSettings::refreshDaemonList() const {
        defaultDaemon->clear();

        for (const Daemon &d: settings.getDaemonList())
            defaultDaemon->addItem(d.name);

        defaultDaemon->setCurrentIndex(settings.getDefaultDaemon());
    }

    void ClientSettings::onApplyClicked() {
        saveGamepadMapping();

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
        settings.setGamepadMappings(gamepadMappings);

        if (!settings.save()) {
            emit logSent(u"failed to write settings to disk"_s);
            emit saved(false);

        } else {
            emit logSent(u"settings saved successfully"_s);
            emit saved(true);
        }
    }

    void ClientSettings::onGamepadMapChanged(const QString &text) {
        static const QVector<Select *> btnList = {
            gpUp, gpDown, gpLeft, gpRight, gpFastLeft, gpFastRight, gpAction, gpBack, gpScrollUp,
            gpScrollDown, gpScrollTop, gpScrollBottom, gpInputMode, gpNavbarUp, gpNavbarDown, gpRefresh,
            gpApply, gpComboSlot1, gpComboSlot2, gpComboSlot3
        };

        if (text.isEmpty()) {
            for (Select *btn: btnList) {
                btn->setCurrentIndex(-1);
                btn->setEnabled(false);
            }

            gamepadStatus->setText("");
            prevGamepadMapIdx = -1;

        } else {
            for (Select *btn: btnList)
                btn->setEnabled(true);

            if (prevGamepadMapIdx != -1)
                saveGamepadMapping();

            gamepadStatus->setText(!gamepadMap->currentData().toBool() ? "" : u"\uf287"_s);
            setGamepadButtons();
            prevGamepadMapIdx = gamepadMap->currentIndex();
        }
    }

    void ClientSettings::onGamepadMapDeleted() {
        const QString id = gamepadMap->currentText();

        if (id.isEmpty())
            return;

        prevGamepadMapIdx = -1;
        gamepadMappings.remove(id);

        if (!gamepadMap->currentData().toBool()) // remove only if not connected, otherwise, reset it to default
            gamepadMap->removeItem(gamepadMap->currentIndex());
        else
            setGamepadButtons();
    }

    void ClientSettings::onGamepadAdded(const QString &id) const {
        if (gamepadMap->findText(id) == -1) {
            gamepadMap->addItem(id, true);

        } else if (id == gamepadMap->currentText()) {
            gamepadMap->setItemData(gamepadMap->currentIndex(), true);
            gamepadStatus->setText(u"\uf287"_s);

        } else {
            gamepadMap->setItemData(gamepadMap->findText(id), true);
        }
    }

    void ClientSettings::onGamepadRemoved(const QString &id) const {
        if (id == gamepadMap->currentText()) {
            gamepadMap->setItemData(gamepadMap->currentIndex(), false);
            gamepadStatus->setText("");

        } else {
            gamepadMap->setItemData(gamepadMap->findText(id), false);
        }
    }
}
