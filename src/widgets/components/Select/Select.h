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
#include <QComboBox>
#include <QStyledItemDelegate>

#include "../PInputItem.h"
#include "../../../classes/Settings.h"

namespace PWT::UI {
    class Select final: public QComboBox, public PInputItem {
        Q_OBJECT

    private:
        class StyleItemDelegate final: public QStyledItemDelegate {
        private:
            const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();

        public:
            void paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &idx) const override;
        };

        class ViewEvents final: public QObject {
        public:
            explicit ViewEvents(QObject *parent): QObject(parent) {}

            bool eventFilter(QObject *watched, QEvent *event) override;
        };

        const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();

    protected:
        void paintEvent(QPaintEvent *) override;
        void keyPressEvent(QKeyEvent *) override {}
        void keyReleaseEvent(QKeyEvent *) override {}

    public:
        Select();

        void activate(bool gamepad) override;
        void handleButton(ButtonKey key) override;
    };
}