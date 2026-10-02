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
#include <QStandardPaths>
#include <QDir>

#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include "classes/InputHandler.h"

using namespace Qt::StringLiterals;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    const QString dataPath = getAppDataPath();

    appSettings.setPath(dataPath);

    const bool isDefaultSettings = !appSettings.load();
    QVBoxLayout *windowLyt = new QVBoxLayout();
    QHBoxLayout *mainLyt = new QHBoxLayout();
    PWT::App::InputHandler *inputHandler = new PWT::App::InputHandler(this);
    QPalette pal = palette();

    navbar = new PWT::UI::Navbar();
    pages = new QStackedWidget();
    statusbar = new PWT::UI::Statusbar();
    home = new PWT::UI::PAGE::Home();
    logs = new PWT::UI::PAGE::Logs();
    clientSettings = new PWT::UI::PAGE::ClientSettings();
    daemons = new PWT::UI::PAGE::Daemons();

    logs->write(QString("client data path: %1").arg(dataPath));

    if (isDefaultSettings)
        logs->write(u"failed to load client settings, using defaults"_s);

    installEventFilter(inputHandler);
    pal.setColor(QPalette::Window, appSettings.getStyle()->mainWindowBackground());
    pal.setColor(QPalette::WindowText, appSettings.getStyle()->mainWindowText());
    setPalette(pal);
    pages->addWidget(home);
    pages->addWidget(logs);
    pages->addWidget(clientSettings);
    pages->addWidget(daemons);
    pages->setCurrentIndex(0);

    mainLyt->addWidget(navbar);
    mainLyt->addWidget(pages);
    windowLyt->addLayout(mainLyt);
    windowLyt->addWidget(statusbar);
    ui->centralwidget->setLayout(windowLyt);

    QObject::connect(navbar, &PWT::UI::Navbar::pageChanged, this, &MainWindow::navbarPageChanged);
    QObject::connect(inputHandler, &PWT::App::InputHandler::navbarUpKey, this, &MainWindow::navbarUpKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::navbarDownKey, this, &MainWindow::navbarDownKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::refreshKey, this, &MainWindow::refreshKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::applyKey, this, &MainWindow::applyKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::buttonPressed, this, &MainWindow::buttonPressed);
    QObject::connect(clientSettings, &PWT::UI::PAGE::ClientSettings::logSent, this, &MainWindow::onLogSent);
    QObject::connect(daemons, &PWT::UI::PAGE::Daemons::logSent, this, &MainWindow::onLogSent);
    QObject::connect(daemons, &PWT::UI::PAGE::Daemons::activeDaemonChanged, this, &MainWindow::onActiveDaemonChanged);
    QObject::connect(daemons, &PWT::UI::PAGE::Daemons::daemonListChanged, this, &MainWindow::onDaemonListChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::getAppDataPath() const {
    QString path = QString("%1/PowerTuner").arg(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
    const QDir qdir;

    if (!qdir.exists(path) && !qdir.mkpath(path))
        return "";

    return path;
}

void MainWindow::navbarPageChanged(const int idx) const {
    pages->setCurrentIndex(idx);
}

void MainWindow::navbarUpKeyPressed() const {
    navbar->switchPageUp();
}

void MainWindow::navbarDownKeyPressed() const {
    navbar->switchPageDown();
}

void MainWindow::refreshKeyPressed() const {
}

void MainWindow::applyKeyPressed() const {
}

void MainWindow::buttonPressed(const PWT::ButtonKey key, const bool gamepad) const {
    static_cast<PWT::UI::PAGE::PPage *>(pages->currentWidget())->handleButton(key, gamepad);
}

void MainWindow::onLogSent(const QString &msg, const std::source_location loc) const {
    logs->write(msg, loc);
    navbar->setIndicator(1);
}

void MainWindow::onActiveDaemonChanged() {

}

void MainWindow::onDaemonListChanged() const {
    clientSettings->refreshDaemonList();
}
