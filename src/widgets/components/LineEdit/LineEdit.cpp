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
#include <QKeyEvent>

#include "LineEdit.h"

namespace PWT::UI {
    LineEdit::LineEdit(): PInputItem(this) {
        QPalette pal = palette();

        pal.setBrush(QPalette::Base, Qt::transparent);
        pal.setBrush(QPalette::Text, appTheme->textEditText());
        setPalette(pal);
        setFocusPolicy(Qt::NoFocus);
    }

    void LineEdit::paintEvent(QPaintEvent *event) {
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(isFocused && !isActive ? QPen(appTheme->focusBorder(), 2) : appTheme->textEditBorder());
        p.setBrush(!isEnabled() ? appTheme->disabled() : (isActive ? appTheme->lineEditActive() : appTheme->textEdit()));
        p.drawRoundedRect(rect(), 5, 5);

        QLineEdit::paintEvent(event);
    }

    void LineEdit::keyReleaseEvent(QKeyEvent *event) {
        if (static_cast<Qt::Key>(event->key()) == Qt::Key_Return && isActive) {
            handleButton(ButtonKey::Back);
            emit returnPressed();
            return;
        }

        QLineEdit::keyReleaseEvent(event);
    }

    void LineEdit::mouseReleaseEvent(QMouseEvent *event) {
        if (!isActive && event->button() == Qt::LeftButton)
            emit mouseActivation(this);
    }

    void LineEdit::activate(const bool gamepad) {
        if (gamepad) {
            emit showVKeyboard(text());
            return;
        }

        isActive = true;
        setFocus();
        update();
    }

    void LineEdit::handleButton(const ButtonKey key) {
        switch (key) {
            case ButtonKey::Back: {
                isActive = false;
                clearFocus();
                update();
            }
                break;
            default:
                break;
        }
    }

    void LineEdit::writeVKeyboardText(const QString &text) {
        clear();
        setText(text);
    }
}
