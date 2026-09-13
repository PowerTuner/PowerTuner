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
#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include "classes/InputHandler.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    appSettings.load();

    const std::shared_ptr<PWT::Style::Style> style = appSettings.getStyle();
    QVBoxLayout *windowLyt = new QVBoxLayout();
    QHBoxLayout *mainLyt = new QHBoxLayout();
    PWT::App::InputHandler *inputHandler = new PWT::App::InputHandler(this);
    QPalette pal = palette();

    navbar = new PWT::UI::Navbar();
    pages = new QStackedWidget();
    statusbar = new PWT::UI::Statusbar();
    home = new PWT::UI::PAGE::Home();
    logs = new PWT::UI::PAGE::Logs();

    installEventFilter(inputHandler);
    pal.setColor(QPalette::Window, style->mainWindowBackground());
    pal.setColor(QPalette::WindowText, style->mainWindowText());
    setPalette(pal);
    pages->addWidget(home);
    pages->addWidget(logs);
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
}

MainWindow::~MainWindow() {
    delete ui;
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