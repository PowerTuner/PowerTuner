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
#include <QScrollBar>

#include "PPage.h"

namespace PWT::UI::PAGE {
    PPage::PPage() {
        QVBoxLayout *pageLyt = new QVBoxLayout();

        lyt = new QVBoxLayout();
        scrollArea = new ScrollArea(Qt::Vertical, true);

        lyt->setContentsMargins(0, 0, 0, 0);
        scrollArea->widget()->setLayout(lyt);
        pageLyt->addWidget(scrollArea);

        setLayout(pageLyt);
        setFocusPolicy(Qt::NoFocus);
    }

    bool PPage::isValidFocusIndex() const {
        return focusedIdx >= 0 && focusedIdx < inputList.size();
    }

    bool PPage::tryFocusComponent(const int idx) {
        const auto [component, pinput] = inputList[idx];

        if (component->isHidden() || !component->isEnabled())
            return false;

        if (isValidFocusIndex())
            inputList[focusedIdx].second->setFocused(false);

        scrollArea->ensureWidgetVisible(component);
        pinput->setFocused(true);
        focusedIdx = idx;
        return true;
    }

    void PPage::collectPageInputs(const QLayout *layout) {
        for (int i=0,l=layout->count(); i<l; ++i) {
            QLayoutItem *itm = layout->itemAt(i);

            if (itm->layout() != nullptr) {
                collectPageInputs(itm->layout());

            } else if (itm->widget() != nullptr) {
                PInputItem *inpt = dynamic_cast<PInputItem *>(itm->widget());

                if (inpt != nullptr)
                    inputList.push_back(std::make_pair(itm->widget(), inpt));
                else if (itm->widget()->layout() != nullptr)
                    collectPageInputs(itm->widget()->layout());
            }
        }
    }

    void PPage::focusFirstWidget() {
        for (int i=0,l=inputList.size(); i<l; ++i) {
            if (tryFocusComponent(i))
                break;
        }
    }

    void PPage::focusLastWidget() {
        for (int i=inputList.size()-1; i>=0; --i) {
            if (tryFocusComponent(i))
                break;
        }
    }

    void PPage::focusPrevNextViewportWidget(const bool next) {
        const QRect wrect = scrollArea->viewport()->rect();
        constexpr QPoint zeroP = {0, 0};
        const int add = next ? 1 : -1;

        if (isValidFocusIndex()) {
            const auto [curComponent, curPInput] = inputList[focusedIdx];
            QRect curCompRect = curComponent->rect();

            curCompRect.moveTopLeft(scrollArea->viewport()->mapFromGlobal(curComponent->mapToGlobal(zeroP)));

            if (wrect.contains(curCompRect))
                return;
        }

        for (int i=focusedIdx,l=inputList.size(); i>=0 && i<l; i+=add) {
            const auto [component, pinput] = inputList[i];
            QRect compRect = component->rect();

            compRect.moveTopLeft(scrollArea->viewport()->mapFromGlobal(component->mapToGlobal(zeroP)));

            if (component->isHidden() || !component->isEnabled() || !wrect.contains(compRect))
                continue;

            if (isValidFocusIndex())
                inputList[focusedIdx].second->setFocused(false);

            pinput->setFocused(true);
            focusedIdx = i;
            break;
        }
    }

    void PPage::deleteWidget(const QWidget *wdg) {
        for (int i=0,l=inputList.size(); i<l; ++i) {
            if (inputList[i].first != wdg)
                continue;

            if (i != focusedIdx) {
                inputList[focusedIdx].second->setFocused(false);
                inputList[focusedIdx].second->handleButton(ButtonKey::Back);
            }

            inputList.removeAt(i);
            focusedIdx = std::clamp(i, 0, static_cast<int>(inputList.size() - 1));;
            break;
        }

        const int add = (focusedIdx + 1) < inputList.size() ? 1 : -1;

        for (int i=focusedIdx,l=inputList.size(); i>=0 && i<l; i+=add) {
            if (tryFocusComponent(i))
                break;
        }
    }

    void PPage::handleButton(const ButtonKey key, const bool gamepad) {
        if (isValidFocusIndex() && inputList[focusedIdx].second->active())
            return inputList[focusedIdx].second->handleButton(key);

        switch (key) {
            case ButtonKey::Up: {
                for (int i=focusedIdx-1,l=inputList.size(); i>=0 && i<l; --i) {
                    if (tryFocusComponent(i))
                        break;
                }
            }
                break;
            case ButtonKey::Down: {
                for (int i=focusedIdx+1,l=inputList.size(); i>=0 && i<l; ++i) {
                    if (tryFocusComponent(i))
                        break;
                }
            }
                break;
            case ButtonKey::Action: {
                if (isValidFocusIndex()) {
                    scrollArea->ensureWidgetVisible(inputList[focusedIdx].first);
                    inputList[focusedIdx].second->activate(gamepad);
                }
            }
                break;
            case ButtonKey::ScrollUp:
            case ButtonKey::ScrollDown: {
                QScrollBar *sbar = scrollArea->verticalScrollBar();
                const bool isUp = key == ButtonKey::ScrollUp;

                sbar->setValue(sbar->value() + (isUp ? -sbar->pageStep() : sbar->pageStep()));
                focusPrevNextViewportWidget(!isUp);
            }
                break;
            case ButtonKey::ScrollTop: {
                if (scrollArea->verticalScrollBar()->maximum() == 0)
                    break;

                scrollArea->verticalScrollBar()->setValue(0);
                focusFirstWidget();
            }
                break;
            case ButtonKey::ScrollBottom: {
                if (scrollArea->verticalScrollBar()->maximum() == 0)
                    break;

                scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
                focusLastWidget();
            }
                break;
            default:
                break;
        }
    }

    void PPage::writeVKeyboardText(const QString &text) const {
        inputList[focusedIdx].second->writeVKeyboardText(text);
    }

    void PPage::onPinputMouseActivation(PInputItem *itm) {
        int idx = 0;

        for (const auto [component, pinput]: inputList) {
            if (pinput == itm)
                break;

            ++idx;
        }

        if (isValidFocusIndex()) {
            inputList[focusedIdx].second->handleButton(ButtonKey::Back);
            inputList[focusedIdx].second->setFocused(false);
        }

        itm->setFocused(true);
        itm->activate(false);
        focusedIdx = idx;
    }
}
