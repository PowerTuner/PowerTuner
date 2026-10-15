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
#include <QLabel>

#include "Daemons.h"
#include "../../widgets/components/Button/Button.h"
#include "../PageUtils.h"

namespace PWT::UI::PAGE {
    using namespace Qt::StringLiterals;

    Daemons::Daemons() {
        QHBoxLayout *addLyt = new QHBoxLayout();
        QHBoxLayout *addBtnLyt = new QHBoxLayout();
        Button *addBtn = new Button(u"Add"_s);

        daemonListLyt = new QVBoxLayout();
        activeDaemon = new Select();
        daemonName = new LineEdit();
        daemonAddr = new LineEdit();
        daemonPort = new SpinBox();

        for (const auto &daemon: settings.getDaemonList()) {
            addDaemon(daemon);
            activeDaemon->addItem(daemon.name);
        }

        activeDaemon->setCurrentIndex(settings.getDefaultDaemon());
        daemonPort->setRange(1024, UINT16_MAX);
        daemonPort->setValue(56000);

        addBtnLyt->addStretch();
        addBtnLyt->addWidget(addBtn);
        addLyt->addLayout(makeVItem(u"Name"_s, daemonName));
        addLyt->addLayout(makeVItem(u"Address"_s, daemonAddr));
        addLyt->addLayout(makeVItem(u"Port"_s, daemonPort));
        addLyt->itemAt(0)->setAlignment(Qt::AlignLeft);
        addLyt->itemAt(1)->setAlignment(Qt::AlignLeft);
        addLyt->itemAt(2)->setAlignment(Qt::AlignLeft);

        lyt->addLayout(makeHItem(u"Active daemon"_s, activeDaemon));
        lyt->addSpacing(10);
        lyt->addLayout(makeTitle(u"Add daemon"_s, u"\uf055"_s));
        lyt->addLayout(addLyt);
        lyt->addSpacing(6);
        lyt->addLayout(addBtnLyt);
        lyt->addLayout(makeTitle(u"Daemons"_s, u"\uf6d5"_s));
        lyt->addLayout(daemonListLyt);
        lyt->addStretch();
        collectPageInputs(lyt);
        focusFirstWidget();

        QObject::connect(daemonName, &LineEdit::mouseActivation, this, &Daemons::onPinputMouseActivation);
        QObject::connect(daemonName, &LineEdit::showVKeyboard, this, &Daemons::showVKeyboard);
        QObject::connect(daemonAddr, &LineEdit::mouseActivation, this, &Daemons::onPinputMouseActivation);
        QObject::connect(daemonAddr, &LineEdit::showVKeyboard, this, &Daemons::showVKeyboard);
        QObject::connect(daemonPort, &SpinBox::mouseActivation, this, &Daemons::onPinputMouseActivation);
        QObject::connect(daemonPort, &SpinBox::showVKeyboard, this, &Daemons::showVKeyboard);
        QObject::connect(addBtn, &Button::clicked, this, &Daemons::onAddDaemonClicked);
        QObject::connect(activeDaemon, &Select::currentIndexChanged, this, &Daemons::onActiveDaemonChanged);
    }

    void Daemons::addDaemon(const Daemon &d) const {
        QWidget *handle = new QWidget();
        QHBoxLayout *daemonLyt = new QHBoxLayout(handle);
        QHBoxLayout *labelLyt = new QHBoxLayout();
        Button *delBtn = new Button(u"Delete"_s);

        handle->setProperty("name", d.name);
        handle->setProperty("adr", d.address);
        handle->setProperty("port", d.port);
        labelLyt->addWidget(new QLabel(u"\uf390 %1"_s.arg(d.name)));
        labelLyt->addSpacing(16);
        labelLyt->addWidget(new QLabel(u"\uf6ff %1:%2"_s.arg(d.address).arg(d.port)));
        daemonLyt->addLayout(labelLyt);
        daemonLyt->addStretch();
        daemonLyt->addWidget(delBtn);
        daemonListLyt->addWidget(handle);

        QObject::connect(delBtn, &Button::clicked, this, &Daemons::onDeleteDaemonClicked);
    }

    void Daemons::onAddDaemonClicked() {
        const QString name = daemonName->text();
        const QString adr = daemonAddr->text();

        if (name.isEmpty() || adr.isEmpty())
            return;

        const Daemon d = {name, adr, static_cast<uint16_t>(daemonPort->value())};

        addDaemon(d);
        collectPageInputs(daemonListLyt->itemAt(daemonListLyt->count() - 1)->widget()->layout());
        daemonName->clear();
        daemonAddr->clear();
        activeDaemon->addItem(d.name);
        settings.addDaemon(d);
        emit logSent(!settings.save() ? u"failed to save daemons changes to disk"_s : u"%1 daemon saved successfully"_s.arg(name));
        emit daemonListChanged();
    }

    void Daemons::onDeleteDaemonClicked() {
        QWidget *w = qobject_cast<QWidget *>(QObject::sender());

        if (w == nullptr)
            return;

        const QWidget *handle = w->parentWidget();
        const QLayoutItem *itm = daemonListLyt->takeAt(daemonListLyt->indexOf(handle));
        const Daemon d = {handle->property("name").toString(), handle->property("adr").toString(), static_cast<uint16_t>(handle->property("port").toUInt())};

        itm->widget()->deleteLater();
        delete itm;
        deleteWidget(w);
        activeDaemon->removeItem(activeDaemon->findText(d.name));
        settings.removeDaemon(d);
        emit logSent(!settings.save() ? u"failed to save daemons changes to disk"_s : u"%1 daemon removed successfully"_s.arg(d.name));
        emit daemonListChanged();
    }

    void Daemons::onActiveDaemonChanged(const int) {
        emit activeDaemonChanged();
    }
}
