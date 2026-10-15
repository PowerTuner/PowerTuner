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
#include <QScrollBar>
#include <QScroller>

#include "TextEdit.h"
#include "../../../classes/Settings.h"

namespace PWT::UI {
    TextEdit::TextEdit(): PInputItem(this) {
        QPalette pal = viewport()->palette();

        QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);
        pal.setBrush(QPalette::Base, appTheme->textEdit());
        pal.setBrush(QPalette::Text, appTheme->textEditText());
        viewport()->setPalette(pal);
        setFocusPolicy(Qt::NoFocus);
        setWordWrapMode(QTextOption::NoWrap);
    }

    void TextEdit::paintEvent(QPaintEvent *event) {
        QTextEdit::paintEvent(event);

        QPainter p(viewport());

        if (isFocused || isActive) {
            p.setRenderHint(QPainter::Antialiasing);
            p.setPen(QPen(isActive ? appTheme->textEditActive() : appTheme->focusBorder(), 2));
            p.drawRoundedRect(viewport()->rect(), 4, 4);
        }

        if (drawCursor) {
            const QRect rect = cursorRect(textCursor());

            p.setPen(appTheme->textEditText());
            p.drawLine(rect.topLeft(), rect.bottomLeft());
        }
    }

    void TextEdit::activate(const bool gamepad) {
        isActive = true;
        update();
    }

    void TextEdit::handleButton(const ButtonKey key) {
        switch (key) {
            case ButtonKey::Up:
            case ButtonKey::Down: {
                QScrollBar *sb = verticalScrollBar();

                if (sb)
                    sb->setValue(sb->value() + (key == ButtonKey::Up ? -2 : 2));
            }
                break;
            case ButtonKey::Left:
            case ButtonKey::Right: {
                QScrollBar *sb = horizontalScrollBar();

                if (sb)
                    sb->setValue(sb->value() + (key == ButtonKey::Left ? -2 : 2));
            }
                break;
            case ButtonKey::ScrollUp:
            case ButtonKey::ScrollDown: {
                QScrollBar *sb = verticalScrollBar();

                if (sb)
                    sb->setValue(sb->value() + (key == ButtonKey::ScrollUp ? -sb->pageStep() : sb->pageStep()));
            }
                break;
            case ButtonKey::ScrollTop:
            case ButtonKey::ScrollBottom: {
                QScrollBar *sb = horizontalScrollBar();

                if (sb)
                    sb->setValue(sb->value() + (key == ButtonKey::ScrollTop ? -sb->pageStep() : sb->pageStep()));
            }
                break;
            case ButtonKey::Back: {
                isActive = false;
                update();
            }
                break;
            default:
                break;
        }
    }
}
