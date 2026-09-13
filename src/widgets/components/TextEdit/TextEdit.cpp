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
#include <QPainter>

#include "TextEdit.h"
#include "../../../classes/Settings.h"

namespace PWT::UI {
    TextEdit::TextEdit() {
        const std::shared_ptr<Style::Style> appTheme = App::Settings::get().getStyle();
        QPalette pal = viewport()->palette();

        pal.setBrush(QPalette::Base, appTheme->textEdit());
        pal.setBrush(QPalette::Text, appTheme->textEditText());
        viewport()->setPalette(pal);
        setFocusPolicy(Qt::NoFocus);
    }

    void TextEdit::paintEvent(QPaintEvent *event) {
        QTextEdit::paintEvent(event);

        if (isFocused) {
            QPainter p(viewport());

            p.setRenderHint(QPainter::Antialiasing);
            p.setPen(QPen(appTheme->focusBorder(), 2));
            p.drawRoundedRect(viewport()->rect(), 4, 4);
        }
    }

    void TextEdit::setFocused(const bool enable) {
        isFocused = enable;
        update();
    }

    void TextEdit::handleButton(const ButtonKey key, const bool gamepad) {

    }
}
