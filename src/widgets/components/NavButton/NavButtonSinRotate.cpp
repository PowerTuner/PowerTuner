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

#include "NavButtonSinRotate.h"

namespace PWT::UI {
    NavButtonSinRotate::NavButtonSinRotate(const QString &title, const QString &icon): NavButton(title, icon) {
        anim = new QVariantAnimation(this);
        anim->setStartValue(0);
        anim->setEndValue(360);
        anim->setDuration(1000);
        anim->setLoopCount(-1);
        anim->setEasingCurve(QEasingCurve::SineCurve);

        QObject::connect(anim, &QVariantAnimation::valueChanged, this, &NavButtonSinRotate::rotationChanged);
    }

    void NavButtonSinRotate::paintIcon(QPainter &p) const {
        const QPoint centerP = rect().center();

        p.save();
        p.translate(centerP);
        p.rotate(rotation);
        p.translate(-centerP);

        p.setPen(appTheme->navButtonIcon());
        p.setBrush(appTheme->navButtonIcon());
        p.drawText(rect(), Qt::AlignCenter, text());
        p.restore();
    }

    void NavButtonSinRotate::startAnimation() const {
        if (anim->state() != QAbstractAnimation::Running)
            anim->start();
    }

    void NavButtonSinRotate::stopAnimation() {
        anim->stop();
        rotation = 0;
        update();
    }

    void NavButtonSinRotate::rotationChanged(const QVariant &v) {
        rotation = v.toReal();
        update();
    }
}
