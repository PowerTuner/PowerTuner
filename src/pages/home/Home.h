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
#include "../../widgets/pages/Label/Label.h"

namespace PWT::UI::PAGE {
    class Home final: public PPage {
        Q_OBJECT

    private:
        static inline const QString noValue = "-";
        Label *product;
        Label *manufacturer;
        Label *os;
        Label *kernel;
        Label *arch;
        Label *biosVendor;
        Label *biosVersion;
        Label *biosDate;
        Label *ram;
        Label *swap;
        Label *cpuBrand;
        Label *cpuCodename;
        Label *cpuTechNode;
        Label *cpuVendor;
        Label *cpuFamily;
        Label *cpuExtFamily;
        Label *cpuModel;
        Label *cpuExtModel;
        Label *cpuCores;
        Label *cpuThreads;
        Label *cpuStepping;
        Label *cpuL1DCache;
        Label *cpuL1ICache;
        Label *cpuL2Cache;
        Label *cpuL3Cache;

    public:
        Home();

        void handleButton(ButtonKey key, bool gamepad) override;
    };
}