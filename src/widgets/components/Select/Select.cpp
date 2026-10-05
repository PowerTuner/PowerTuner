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
#include <QEvent>
#include <QAbstractItemView>

#include "Select.h"

namespace PWT::UI {
    Select::Select(): PInputItem(this) {
        setItemDelegate(new StyleItemDelegate);
        view()->installEventFilter(new ViewEvents(this));
        view()->setFocusPolicy(Qt::NoFocus);
        setMinimumWidth(40);
        setFocusPolicy(Qt::NoFocus);
        setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }

    void Select::StyleItemDelegate::paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &idx) const {
        const QRect itmRect = opt.rect;

        p->save();
        p->setRenderHint(QPainter::Antialiasing);

        p->setPen(Qt::NoPen);
        p->setBrush(opt.state & QStyle::State_Selected ? appTheme->selectComboBoxListItmSelected() : appTheme->selectComboBox());
        p->drawRect(itmRect);

        p->setPen(appTheme->selectComboBoxText());
        p->drawText(itmRect.adjusted(10, 0, -2, 0), Qt::AlignVCenter | Qt::AlignLeft, idx.data(Qt::DisplayRole).toString());
        p->restore();
    }

    bool Select::ViewEvents::eventFilter(QObject *watched, QEvent *event) {
        switch (event->type()) {
            case QEvent::KeyPress:
            case QEvent::KeyRelease:
            case QEvent::ShortcutOverride:
                return true;
            default:
                break;
        }

        return QObject::eventFilter(watched, event);
    }

    void Select::paintEvent(QPaintEvent *) {
        const QRect comboBox = rect();
        const QRect textRect = QRect(comboBox.left() + 5, comboBox.top(), comboBox.width() - 35, comboBox.height());
        const QPoint arrowPos(comboBox.right() - 15, comboBox.center().y());
        const QPolygon arrow = QPolygon({QPoint(arrowPos.x() - 5, arrowPos.y()), QPoint(arrowPos.x() + 5, arrowPos.y()), QPoint(arrowPos.x(), arrowPos.y() + 5)});
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(isFocused && !isActive ? QPen(appTheme->focusBorder(), 2) : appTheme->selectComboBoxBorder());
        p.setBrush(!isEnabled() ? appTheme->disabled() : (isActive ? appTheme->selectComboBoxActive() : appTheme->selectComboBox()));
        p.drawRoundedRect(comboBox, 5, 5);

        p.setPen(appTheme->selectComboBoxText());
        p.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, currentText());

        p.setPen(Qt::NoPen);
        p.setBrush(appTheme->selectComboBoxText());
        p.drawPolygon(arrow);
    }

    void Select::activate() {
        isActive = true;
        update();
    }

    void Select::handleButton(const ButtonKey key) {
        switch (key) {
            case ButtonKey::Up: {
                const int prev = currentIndex() - 1;

                if (prev >= 0)
                    setCurrentIndex(prev);
            }
                break;
            case ButtonKey::Down: {
                const int next = currentIndex() + 1;

                if (next < count())
                    setCurrentIndex(next);
            }
                break;
            case ButtonKey::Action:
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
