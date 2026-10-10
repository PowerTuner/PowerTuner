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
#include <QApplication>
#include <QFontDatabase>

#include "mainwindow.h"
#include "../version.h"

using namespace Qt::StringLiterals;

[[nodiscard]]
static QFont loadFonts() {
    const int notoSans = QFontDatabase::addApplicationFont(u":/fonts/noto-sans-regular"_s);
    QFont font;

    QFontDatabase::addApplicationFont(u":/fonts/fontawesome-solid"_s);
    QFontDatabase::addApplicationFont(u":/fonts/fontawesome-brands"_s);

    font.setFamilies(QFontDatabase::applicationFontFamilies(notoSans));
    font.setPointSize(14);
    font.setWeight(QFont::Medium);

    QApplication::setFont(font);
    return font;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    QApplication::setQuitOnLastWindowClosed(false);
    w.setFont(loadFonts());
    w.setWindowTitle(u"PowerTuner %1.%2"_s.arg(VER_MAJOR).arg(VER_MINOR));
    w.resize(1024, 600);
    w.show();

    return QApplication::exec();
}
