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
#include <QAbstractButton>

#include "../../../classes/Settings.h"

namespace PWT::UI {
    class NavButton: public QAbstractButton {
        Q_OBJECT

    private:
        static constexpr int btnWH = 42;
        static constexpr int markW = 26;
        static constexpr int markH = 3;
        static constexpr QRect markRect {(btnWH / 2) - (markW / 2), btnWH - markH - 1, markW, markH};
        static constexpr QRect indicatorRect {btnWH - 10, 10, 9, 9};
        bool isHovered = false;
        bool isActive = false;
        bool hasIndicator = false;

    protected:
        const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();

        void paintEvent(QPaintEvent *) override;
        void enterEvent(QEnterEvent *) override;
        void leaveEvent(QEvent *) override;
        virtual void paintIcon(QPainter &p) const;

    public:
        NavButton(const QString &title, const QString &icon);

        void setActive(bool active);
        void setIndicator(bool enable);
    };
}
