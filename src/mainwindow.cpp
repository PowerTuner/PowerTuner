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

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    appSettings.load();

    const std::shared_ptr<PWT::Style::Style> style = appSettings.getStyle();
    QVBoxLayout *windowLyt = new QVBoxLayout();
    QHBoxLayout *mainLyt = new QHBoxLayout();

    QPalette pal = palette();

    navbar = new PWT::UI::Navbar();
    pages = new QStackedWidget();
    statusbar = new PWT::UI::Statusbar();
    home = new PWT::UI::PAGE::Home();
    logs = new PWT::UI::PAGE::Logs();

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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::navbarPageChanged(const int idx) const {
    pages->setCurrentIndex(idx);
}
