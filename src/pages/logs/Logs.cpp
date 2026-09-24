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
#include <QFileInfo>
#include <QDateTime>

#include "Logs.h"
#include "../../widgets/components/Button/Button.h"

namespace PWT::UI::PAGE {
    using namespace Qt::StringLiterals;

    Logs::Logs() {
        Button *clearBtn = new Button(u"Clear"_s);

        logsBox = new TextEdit();

        logsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        logsBox->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
        logsBox->setReadOnly(true);
        logsBox->setFontPointSize(12);
        clearBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        lyt->addWidget(logsBox);
        lyt->addWidget(clearBtn, 0, Qt::AlignRight);
        collectPageInputs(lyt);
        focusFirstWidget();

        QObject::connect(clearBtn, &Button::clicked, this, &Logs::clearBtnClicked);
    }

    void Logs::write(const QString &msg, const std::source_location loc) const {
        const QFileInfo finfo(loc.file_name());
        const QDateTime now = QDateTime::currentDateTime();

        logsBox->append(QString("(%1) %2[%3:%4]: %5").arg(now.toString("MMMM ddd d hh:mm"), finfo.baseName()).arg(loc.line()).arg(loc.column()).arg(msg));
    }

    void Logs::clearBtnClicked() const {
        logsBox->clear();
    }
}
