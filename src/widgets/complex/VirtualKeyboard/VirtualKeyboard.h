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
#include <QGridLayout>

#include "../../components/TextEdit/TextEdit.h"

namespace PWT::UI {
    class VirtualKeyboard final: public QWidget {
        Q_OBJECT

    private:
        struct KBNode final {
            QWidget *kb;
            QGridLayout *lyt;
            KBNode *next = nullptr;
            bool hasCase = false;
            bool upper = false;
            int col = 0;
            int row = 0;
        };

        KBNode *keyboard;
        TextEdit *textbox;

        [[nodiscard]] QGridLayout *makeAlphanumKb() const;

    public:
        explicit VirtualKeyboard(QWidget *parent);
        ~VirtualKeyboard() override;

        void handleButton(GamepadButton button);
        void setText(const QString &text) const;

    private slots:
        void onButtonPressed() const;

    signals:
        void hideKeyboard();
        void writeText(const QString &text);
    };
}
