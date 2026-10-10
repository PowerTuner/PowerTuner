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
#include <QSystemTrayIcon>
#include <QScopedPointer>

#include "classes/Settings.h"
#include "widgets/complex/Navbar/Navbar.h"
#include "widgets/complex/Statusbar/Statusbar.h"
#include "pages/home/Home.h"
#include "pages/logs/Logs.h"
#include "pages/clientSettings/ClientSettings.h"
#include "pages/daemons/Daemons.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final: public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QScopedPointer<QSystemTrayIcon> trayIcon;
    PWT::App::Settings &appSettings = PWT::App::Settings::get();
    QStackedWidget *pages;
    PWT::UI::Navbar *navbar;
    PWT::UI::Statusbar *statusbar;
    PWT::UI::PAGE::Home *home;
    PWT::UI::PAGE::Logs *logs;
    PWT::UI::PAGE::ClientSettings *clientSettings;
    PWT::UI::PAGE::Daemons *daemons;

    [[nodiscard]] QString getAppDataPath() const;
    void setTrayIcon();
    void setStartup() const;

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void navbarPageChanged(int idx) const;
    void navbarUpKeyPressed() const;
    void navbarDownKeyPressed() const;
    void refreshKeyPressed() const;
    void applyKeyPressed() const;
    void buttonPressed(PWT::ButtonKey key, bool gamepad) const;
    void onToggleAppWindow();
    void onLogSent(const QString &msg, std::source_location loc) const;
    void onActiveDaemonChanged();
    void onDaemonListChanged() const;
    void onSettingsSaved(bool writeResult);
    void onTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
};
