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
#include "Navbar.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    Navbar::Navbar() {
        QVBoxLayout *navLyt = new QVBoxLayout();
        QVBoxLayout *actionsLyt = new QVBoxLayout();
        NavButton *deviceNav = new NavButton(u"Device"_s, u"\ue4e5"_s);
        NavButton *logsNav = new NavButton(u"Logs"_s, u"\uf022"_s);
        NavButton *settingsNav = new NavButton(u"Settings"_s, u"\uf013"_s);

        lyt = new QVBoxLayout();
        active = deviceNav;
        scrollArea = new ScrollArea(Qt::Vertical, true);
        refreshBtn = new NavButtonSinRotate(u"Refresh"_s, u"\uf2f1"_s);
        applyBtn = new NavButton(u"Apply"_s, u"\uf019"_s);

        setFixedWidth(deviceNav->width() + 2);
        deviceNav->setActive(true);
        scrollArea->widget()->setLayout(lyt);
        setFocusPolicy(Qt::NoFocus);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->setAlignment(Qt::AlignTop);
        lyt->addWidget(deviceNav);
        lyt->addWidget(logsNav);
        lyt->addWidget(settingsNav);
        actionsLyt->setContentsMargins(0, 0, 0, 0);
        actionsLyt->addWidget(refreshBtn);
        actionsLyt->addWidget(applyBtn);
        navLyt->setContentsMargins(0, 0, 0, 0);
        navLyt->addWidget(scrollArea);
        navLyt->addStretch();
        navLyt->addLayout(actionsLyt);

        setLayout(navLyt);

        QObject::connect(deviceNav, &NavButton::clicked, this, &Navbar::onNavButtonClicked);
        QObject::connect(settingsNav, &NavButton::clicked, this, &Navbar::onNavButtonClicked);
        QObject::connect(logsNav, &NavButton::clicked, this, &Navbar::onNavButtonClicked);
        QObject::connect(refreshBtn, &NavButton::clicked, this, &Navbar::onRefreshClicked);
        QObject::connect(applyBtn, &NavButton::clicked, this, &Navbar::onApplyClicked);
    }

    void Navbar::switchPage(const int idx, NavButton *btn) {
        if (btn == nullptr)
            return;

        active->setActive(false);
        btn->setActive(true);
        active = btn;

        scrollArea->ensureWidgetVisible(active);
        emit pageChanged(idx);
    }

    void Navbar::switchPageUp() {
        const int idx = lyt->indexOf(active) - 1;
        const int prev = idx < 0 ? (lyt->count() - 1) : idx;

        switchPage(prev, qobject_cast<NavButton *>(lyt->itemAt(prev)->widget()));
    }

    void Navbar::switchPageDown() {
        const int idx = lyt->indexOf(active) + 1;
        const int next = idx >= lyt->count() ? 0 : idx;

        switchPage(next, qobject_cast<NavButton *>(lyt->itemAt(next)->widget()));
    }

    void Navbar::onNavButtonClicked() {
        NavButton *btn = qobject_cast<NavButton *>(QObject::sender());

        if (btn != nullptr && btn != active) [[likely]]
            switchPage(lyt->indexOf(btn), btn);
    }

    void Navbar::onRefreshClicked() {
        emit refreshUI();
    }

    void Navbar::onApplyClicked() {
        emit applyChanges();
    }
}
