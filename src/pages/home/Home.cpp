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
#include "Home.h"
#include "../../widgets/pages/Title/Title.h"

namespace PWT::UI::PAGE {
    using namespace Qt::StringLiterals;

    Home::Home() {
        product = new Label(u"Product"_s, noValue);
        manufacturer = new Label(u"Manufacturer"_s, noValue);
        os = new Label(u"Operating system"_s, noValue);
        kernel = new Label(u"Kernel"_s, noValue);
        arch = new Label(u"Architecture"_s, noValue);
        biosVendor = new Label(u"Bios vendor"_s, noValue);
        biosVersion = new Label(u"Bios version"_s, noValue);
        biosDate = new Label(u"Bios data"_s, noValue);
        ram = new Label(u"RAM"_s, noValue);
        cpuBrand = new Label(u"Brand"_s, noValue);
        cpuCodename = new Label(u"Codename"_s, noValue);
        cpuTechNode = new Label(u"Technology node"_s, noValue);
        cpuVendor = new Label(u"Vendor"_s, noValue);
        cpuFamily = new Label(u"Family"_s, noValue);
        cpuExtFamily = new Label(u"Extended family"_s, noValue);
        cpuModel = new Label(u"Model"_s, noValue);
        cpuExtModel = new Label(u"Extended model"_s, noValue);
        cpuCores = new Label(u"Cores"_s, noValue);
        cpuThreads = new Label(u"Threads"_s, noValue);
        cpuStepping = new Label(u"Stepping"_s, noValue);
        cpuL1DCache = new Label(u"L1 data cache"_s, noValue);
        cpuL1ICache = new Label(u"L1 instructions cache"_s, noValue);
        cpuL2Cache = new Label(u"L2 cache"_s, noValue);
        cpuL3Cache = new Label(u"L3 cache"_s, noValue);

        lyt->addWidget(new Title(u"\ue4e5 Device"_s));
        lyt->addWidget(product);
        lyt->addWidget(manufacturer);
        lyt->addWidget(os);
        lyt->addWidget(kernel);
        lyt->addWidget(arch);
        lyt->addWidget(biosVendor);
        lyt->addWidget(biosVersion);
        lyt->addWidget(biosDate);
        lyt->addWidget(ram);
        lyt->addWidget(new Title(u"\uf2db CPU"_s));
        lyt->addWidget(cpuBrand);
        lyt->addWidget(cpuCodename);
        lyt->addWidget(cpuTechNode);
        lyt->addWidget(cpuVendor);
        lyt->addWidget(cpuFamily);
        lyt->addWidget(cpuExtFamily);
        lyt->addWidget(cpuModel);
        lyt->addWidget(cpuExtModel);
        lyt->addWidget(cpuCores);
        lyt->addWidget(cpuThreads);
        lyt->addWidget(cpuStepping);
        lyt->addWidget(cpuL1DCache);
        lyt->addWidget(cpuL1ICache);
        lyt->addWidget(cpuL2Cache);
        lyt->addWidget(cpuL3Cache);
        lyt->addStretch();
    }
}
