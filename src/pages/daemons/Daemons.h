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
#include "../PPage.h"
#include "../../widgets/components/Select/Select.h"
#include "../../widgets/components/LineEdit/LineEdit.h"
#include "../../widgets/components/SpinBox/SpinBox.h"
#include "../../classes/Settings.h"

namespace PWT::UI::PAGE {
    class Daemons final: public PPage {
        Q_OBJECT

    private:
        App::Settings &settings = App::Settings::get();
        QVBoxLayout *daemonListLyt;
        Select *activeDaemon;
        LineEdit *daemonName;
        LineEdit *daemonAddr;
        SpinBox *daemonPort;

        void addDaemon(const Daemon &d) const;

    public:
        Daemons();

    private slots:
        void onAddDaemonClicked();
        void onDeleteDaemonClicked();
        void onActiveDaemonChanged();

    signals:
        void activeDaemonChanged();
        void daemonListChanged();
    };
}