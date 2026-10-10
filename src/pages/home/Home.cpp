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
#include "../PageUtils.h"

namespace PWT::UI::PAGE {
    using namespace Qt::StringLiterals;

    Home::Home() {
        product = new Label(u"Product"_s);
        manufacturer = new Label(u"Manufacturer"_s);
        os = new Label(u"Operating system"_s);
        kernel = new Label(u"Kernel"_s);
        arch = new Label(u"Architecture"_s);
        biosVendor = new Label(u"Bios vendor"_s);
        biosVersion = new Label(u"Bios version"_s);
        biosDate = new Label(u"Bios data"_s);
        ram = new Label(u"RAM"_s);
        cpuBrand = new Label(u"Brand"_s);
        cpuCodename = new Label(u"Codename"_s);
        cpuTechNode = new Label(u"Technology node"_s);
        cpuVendor = new Label(u"Vendor"_s);
        cpuFamily = new Label(u"Family"_s);
        cpuExtFamily = new Label(u"Extended family"_s);
        cpuModel = new Label(u"Model"_s);
        cpuExtModel = new Label(u"Extended model"_s);
        cpuCores = new Label(u"Cores"_s);
        cpuThreads = new Label(u"Threads"_s);
        cpuStepping = new Label(u"Stepping"_s);
        cpuL1DCache = new Label(u"L1 data cache"_s);
        cpuL1ICache = new Label(u"L1 instructions cache"_s);
        cpuL2Cache = new Label(u"L2 cache"_s);
        cpuL3Cache = new Label(u"L3 cache"_s);

        lyt->addLayout(makeTitle(u"Device"_s, u"\ue4e5"_s));
        lyt->addWidget(product);
        lyt->addWidget(manufacturer);
        lyt->addWidget(os);
        lyt->addWidget(kernel);
        lyt->addWidget(arch);
        lyt->addWidget(biosVendor);
        lyt->addWidget(biosVersion);
        lyt->addWidget(biosDate);
        lyt->addWidget(ram);
        lyt->addSpacing(14);
        lyt->addLayout(makeTitle(u"CPU"_s, u"\uf2db"_s));
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

    void Home::handleButton(const ButtonKey key, const bool gamepad) {
        switch (key) {
            case ButtonKey::Up:
                PPage::handleButton(ButtonKey::ScrollUp, gamepad);
                break;
            case ButtonKey::Down:
                PPage::handleButton(ButtonKey::ScrollDown, gamepad);
                break;
            default:
                PPage::handleButton(key, gamepad);
                break;
        }
    }
}
