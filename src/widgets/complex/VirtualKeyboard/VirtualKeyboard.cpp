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
#include <QVBoxLayout>
#include <QLabel>

#include "VirtualKeyboard.h"
#include "../../components/Button/Button.h"
#include "../../../classes/Settings.h"

namespace PWT::UI {
    using namespace Qt::StringLiterals;

    VirtualKeyboard::VirtualKeyboard(QWidget *parent): QWidget(parent) {
        const App::Settings &appSettings = App::Settings::get();
        QVBoxLayout *lyt = new QVBoxLayout();
        QLabel *help = new QLabel(u"START: confirm,  SELECT: clear,  X/Y/\u25a1: delete,  L/R: move cursor,  L2: uppercase,  R2: space,  Y/X/\u25b3: switch keyboard,  B/A/\u25cb: close"_s);
        QWidget *alphanum = new QWidget();
        QGridLayout *alphanumLyt = makeAlphanumKb();
        QPalette pal = palette();
        QFont hfont = font();

        keyboard = new KBNode{.kb = alphanum, .lyt = alphanumLyt, .hasCase = true};
        textbox = new TextEdit();

        pal.setColor(QPalette::Window, appSettings.getStyle()->mainWindowBackground());
        textbox->setReadOnly(true);
        textbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        textbox->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
        textbox->setDrawCursor(true);
        hfont.setItalic(true);
        hfont.setPointSize(10);
        help->setFont(hfont);

        alphanum->setLayout(alphanumLyt);
        lyt->addWidget(textbox);
        lyt->addWidget(alphanum);
        lyt->addSpacing(15);
        lyt->addWidget(help);

        setPalette(pal);
        setAutoFillBackground(true);
        setLayout(lyt);
    }

    VirtualKeyboard::~VirtualKeyboard() {
        const KBNode *node = keyboard;

        while (node->next != nullptr && node->next != keyboard) {
            const KBNode *next = node->next;

            delete node;
            node = next;
        }

        delete node;
    }

    QGridLayout *VirtualKeyboard::makeAlphanumKb() const {
        QGridLayout *lyt = new QGridLayout();

        lyt->setAlignment(Qt::AlignCenter);
        lyt->addWidget(new Button(u"1"_s), 0, 0);
        lyt->addWidget(new Button(u"2"_s), 0, 1);
        lyt->addWidget(new Button(u"3"_s), 0, 2);
        lyt->addWidget(new Button(u"4"_s), 0, 3);
        lyt->addWidget(new Button(u"5"_s), 0, 4);
        lyt->addWidget(new Button(u"6"_s), 0, 5);
        lyt->addWidget(new Button(u"7"_s), 0, 6);
        lyt->addWidget(new Button(u"8"_s), 0, 7);
        lyt->addWidget(new Button(u"9"_s), 0, 8);
        lyt->addWidget(new Button(u"0"_s), 0, 9);
        lyt->addWidget(new Button(u"q"_s), 1, 0);
        lyt->addWidget(new Button(u"w"_s), 1, 1);
        lyt->addWidget(new Button(u"e"_s), 1, 2);
        lyt->addWidget(new Button(u"r"_s), 1, 3);
        lyt->addWidget(new Button(u"t"_s), 1, 4);
        lyt->addWidget(new Button(u"y"_s), 1, 5);
        lyt->addWidget(new Button(u"u"_s), 1, 6);
        lyt->addWidget(new Button(u"i"_s), 1, 7);
        lyt->addWidget(new Button(u"o"_s), 1, 8);
        lyt->addWidget(new Button(u"p"_s), 1, 9);
        lyt->addWidget(new Button(u"a"_s), 2, 0);
        lyt->addWidget(new Button(u"s"_s), 2, 1);
        lyt->addWidget(new Button(u"d"_s), 2, 2);
        lyt->addWidget(new Button(u"f"_s), 2, 3);
        lyt->addWidget(new Button(u"g"_s), 2, 4);
        lyt->addWidget(new Button(u"h"_s), 2, 5);
        lyt->addWidget(new Button(u"j"_s), 2, 6);
        lyt->addWidget(new Button(u"k"_s), 2, 7);
        lyt->addWidget(new Button(u"l"_s), 2, 8);
        lyt->addWidget(new Button(u"z"_s), 2, 9);
        lyt->addWidget(new Button(u"x"_s), 3, 0);
        lyt->addWidget(new Button(u"c"_s), 3, 1);
        lyt->addWidget(new Button(u"v"_s), 3, 2);
        lyt->addWidget(new Button(u"b"_s), 3, 3);
        lyt->addWidget(new Button(u"n"_s), 3, 4);
        lyt->addWidget(new Button(u"m"_s), 3, 5);
        lyt->addWidget(new Button(u"_"_s), 3, 6);
        lyt->addWidget(new Button(u"-"_s), 3, 7);
        lyt->addWidget(new Button(u"."_s), 3, 8);
        lyt->addWidget(new Button(u","_s), 3, 9);
        dynamic_cast<PInputItem *>(lyt->itemAtPosition(0, 0)->widget())->setFocused(true);

        for (int i=0,l=lyt->count(); i<l; ++i)
            QObject::connect(static_cast<Button *>(lyt->itemAt(i)->widget()), &Button::clicked, this, &VirtualKeyboard::onButtonPressed);

        return lyt;
    }

    void VirtualKeyboard::handleButton(const GamepadButton button) {
        switch (button) {
            case GamepadButton::DPAD_UP:
            case GamepadButton::DPAD_DOWN:
            case GamepadButton::ANALOG_LEFT_UP:
            case GamepadButton::ANALOG_LEFT_DOWN: {
                const int rowAdd = button == GamepadButton::DPAD_UP || button == GamepadButton::ANALOG_LEFT_UP ? keyboard->row - 1 : keyboard->row + 1;
                const int nextRow = rowAdd >= keyboard->lyt->rowCount() ? 0 : (rowAdd < 0 ? keyboard->lyt->rowCount() - 1 : rowAdd);

                dynamic_cast<PInputItem *>(keyboard->lyt->itemAtPosition(keyboard->row, keyboard->col)->widget())->setFocused(false);
                dynamic_cast<PInputItem *>(keyboard->lyt->itemAtPosition(nextRow, keyboard->col)->widget())->setFocused(true);
                keyboard->row = nextRow;
            }
                break;
            case GamepadButton::DPAD_LEFT:
            case GamepadButton::DPAD_RIGHT:
            case GamepadButton::ANALOG_LEFT_LEFT:
            case GamepadButton::ANALOG_LEFT_RIGHT: {
                const int colAdd = button == GamepadButton::DPAD_LEFT || button == GamepadButton::ANALOG_LEFT_LEFT ?  keyboard->col - 1 : keyboard->col + 1;
                const int nextCol = colAdd >= keyboard->lyt->columnCount() ? 0 : (colAdd < 0 ? keyboard->lyt->columnCount() - 1 : colAdd);

                dynamic_cast<PInputItem *>(keyboard->lyt->itemAtPosition(keyboard->row, keyboard->col)->widget())->setFocused(false);
                dynamic_cast<PInputItem *>(keyboard->lyt->itemAtPosition(keyboard->row, nextCol)->widget())->setFocused(true);
                keyboard->col = nextCol;
            }
                break;
            case GamepadButton::L2: {
                if (!keyboard->hasCase)
                    break;

                const QList<Button *> btnList = keyboard->kb->findChildren<Button *>();

                if (keyboard->upper) {
                    for (Button *btn: btnList)
                        btn->setText(btn->text().toLower());
                } else {
                    for (Button *btn: btnList)
                        btn->setText(btn->text().toUpper());
                }

                keyboard->upper = !keyboard->upper;
            }
                break;
            case GamepadButton::R2: {
                textbox->insertPlainText(u" "_s);
            }
                break;
            case GamepadButton::EAST: {
                emit hideKeyboard();
            }
                break;
            case GamepadButton::NORTH: {
                if (keyboard->next == nullptr)
                    break;

                keyboard->kb->hide();
                keyboard->next->kb->show();

                keyboard = keyboard->next;
            }
                break;
            case GamepadButton::WEST: {
                textbox->textCursor().deletePreviousChar();
            }
                break;
            case GamepadButton::SOUTH: {
                textbox->insertPlainText(static_cast<Button *>(keyboard->lyt->itemAtPosition(keyboard->row, keyboard->col)->widget())->text());
            }
                break;
            case GamepadButton::L1: {
                textbox->moveCursor(QTextCursor::PreviousCharacter);
            }
                break;
            case GamepadButton::R1: {
                textbox->moveCursor(QTextCursor::NextCharacter);
            }
                break;
            case GamepadButton::SELECT: {
                textbox->clear();
            }
                break;
            case GamepadButton::START: {
                emit writeText(textbox->toPlainText());
                emit hideKeyboard();
            }
                break;
            default:
                break;
        }
    }

    void VirtualKeyboard::setText(const QString &text) const {
        textbox->clear();
        textbox->insertPlainText(text);
    }

    void VirtualKeyboard::onButtonPressed() const {
        const Button *btn = qobject_cast<Button *>(QObject::sender());

        if (btn)
            textbox->insertPlainText(btn->text());
    }
}
