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
    QObject::connect(inputHandler, &PWT::App::InputHandler::upKey, this, &MainWindow::upKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::downKey, this, &MainWindow::downKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::leftKey, this, &MainWindow::leftKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::rightKey, this, &MainWindow::rightKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::fastLeftKey, this, &MainWindow::fastLeftKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::fastRightKey, this, &MainWindow::fastRightKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::actionKey, this, &MainWindow::actionKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::backKey, this, &MainWindow::backKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::scrollUpKey, this, &MainWindow::scrollUpKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::scrollDownKey, this, &MainWindow::scrollDownKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::scrollTopKey, this, &MainWindow::scrollTopKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::scrollBottomKey, this, &MainWindow::scrollBottomKeyPressed);
    QObject::connect(inputHandler, &PWT::App::InputHandler::inputModeKey, this, &MainWindow::inputModeKeyPressed);
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

void MainWindow::upKeyPressed(const bool gamepad) const {
}

void MainWindow::downKeyPressed(const bool gamepad) const {
}

void MainWindow::leftKeyPressed(const bool gamepad) const {
}

void MainWindow::rightKeyPressed(const bool gamepad) const {
}

void MainWindow::fastLeftKeyPressed(const bool gamepad) const {
}

void MainWindow::fastRightKeyPressed(const bool gamepad) const {
}

void MainWindow::actionKeyPressed(const bool gamepad) const {
}

void MainWindow::backKeyPressed(const bool gamepad) const {
}

void MainWindow::scrollUpKeyPressed(const bool gamepad) const {
}

void MainWindow::scrollDownKeyPressed(const bool gamepad) const {
}

void MainWindow::scrollTopKeyPressed(const bool gamepad) const {
}

void MainWindow::scrollBottomKeyPressed(const bool gamepad) const {
}

void MainWindow::inputModeKeyPressed(const bool gamepad) const {
}