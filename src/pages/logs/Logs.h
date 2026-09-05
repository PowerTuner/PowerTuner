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
#include <source_location>

#include "../PPage.h"
#include "../../widgets/components/TextEdit/TextEdit.h"

namespace PWT::UI::PAGE {
    class Logs final: public PPage {
        Q_OBJECT

    private:
        TextEdit *logsBox = nullptr;

    public:
        Logs();

        void write(const QString &msg, std::source_location loc = std::source_location::current()) const;

    private slots:
        void clearBtnClicked() const;
    };
}