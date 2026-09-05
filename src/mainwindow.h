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
#pragma once
#include <QMainWindow>
#include <QStackedWidget>

#include "classes/Settings.h"
#include "widgets/complex/Navbar/Navbar.h"
#include "widgets/complex/Statusbar/Statusbar.h"
#include "pages/home/Home.h"
#include "pages/logs/Logs.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    PWT::App::Settings &appSettings = PWT::App::Settings::get();
    QStackedWidget *pages = nullptr;
    PWT::UI::Navbar *navbar = nullptr;
    PWT::UI::Statusbar *statusbar = nullptr;
    PWT::UI::PAGE::Home *home = nullptr;
    PWT::UI::PAGE::Logs *logs = nullptr;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void navbarPageChanged(int idx) const;
};
