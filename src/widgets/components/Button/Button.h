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
#include <QPushButton>

#include "../../../classes/Settings.h"

namespace PWT::UI {
    class Button final: public QPushButton {
        Q_OBJECT

    private:
        const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();
        bool isHovered = false;
        bool isRounded;

    protected:
        void paintEvent(QPaintEvent *) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void enterEvent(QEnterEvent *) override;
        void leaveEvent(QEvent *) override;

    public:
        explicit Button(const QString &text, bool rounded = true);
    };
}