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
        Label *product = nullptr;
        Label *manufacturer = nullptr;
        Label *os = nullptr;
        Label *kernel = nullptr;
        Label *arch = nullptr;
        Label *biosVendor = nullptr;
        Label *biosVersion = nullptr;
        Label *biosDate = nullptr;
        Label *ram = nullptr;
        Label *swap = nullptr;
        Label *cpuBrand = nullptr;
        Label *cpuCodename = nullptr;
        Label *cpuTechNode = nullptr;
        Label *cpuVendor = nullptr;
        Label *cpuFamily = nullptr;
        Label *cpuExtFamily = nullptr;
        Label *cpuModel = nullptr;
        Label *cpuExtModel = nullptr;
        Label *cpuCores = nullptr;
        Label *cpuThreads = nullptr;
        Label *cpuStepping = nullptr;
        Label *cpuL1DCache = nullptr;
        Label *cpuL1ICache = nullptr;
        Label *cpuL2Cache = nullptr;
        Label *cpuL3Cache = nullptr;

    public:
        Home();

        void handleButton(ButtonKey key, bool gamepad) override;
    };
}