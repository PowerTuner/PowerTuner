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
#include "../styles/Style.h"
#include "../styles/StyleType.h"

namespace PWT::App {
    class Settings final {
    private:
        QString path;
        std::shared_ptr<Style::Style> style;
        bool closeToTray = false;
        bool rememberWindowState = true;
        bool runAtStartup = false;
        Style::StyleType styleType = Style::StyleType::VoidPurple;
        Qt::Key kbNavbarUp = Qt::Key_F1;
        Qt::Key kbNavbarDown = Qt::Key_F2;
        Qt::Key kbRefresh = Qt::Key_F5;
        Qt::Key kbApply = Qt::Key_F6;
        Qt::Key kbUp = Qt::Key_Up;
        Qt::Key kbDown = Qt::Key_Down;
        Qt::Key kbLeft = Qt::Key_Left;
        Qt::Key kbRight = Qt::Key_Right;
        Qt::Key kbFastLeft = Qt::Key_Home;
        Qt::Key kbFastRight = Qt::Key_End;
        Qt::Key kbAction = Qt::Key_Return;
        Qt::Key kbBack = Qt::Key_Escape;
        Qt::Key kbScrollUp = Qt::Key_PageUp;
        Qt::Key kbScrollDown = Qt::Key_PageDown;
        Qt::Key kbScrollTop = Qt::Key_F3;
        Qt::Key kbScrollBottom = Qt::Key_F4;
        Qt::Key kbInputMode = Qt::Key_Tab;

        Settings();

        void loadStyle();

    public:
        Settings(const Settings &) = delete;
        Settings &operator=(const Settings &) = delete;

        [[nodiscard]] bool getCloseToTray() const { return closeToTray; }
        [[nodiscard]] bool getRememberWindowState() const { return rememberWindowState; }
        [[nodiscard]] bool getRunAtStartup() const { return runAtStartup; }
        [[nodiscard]] std::shared_ptr<Style::Style> getStyle() const { return style; }
        [[nodiscard]] Style::StyleType getTheme() const { return styleType; }
        [[nodiscard]] Qt::Key getKeyboardNavbarUp() const { return kbNavbarUp; }
        [[nodiscard]] Qt::Key getKeyboardNavbarDown() const { return kbNavbarDown; }
        [[nodiscard]] Qt::Key getKeyboardRefresh() const { return kbRefresh; }
        [[nodiscard]] Qt::Key getKeyboardApply() const { return kbApply; }
        [[nodiscard]] Qt::Key getKeyboardUp() const { return kbUp; }
        [[nodiscard]] Qt::Key getKeyboardDown() const { return kbDown; }
        [[nodiscard]] Qt::Key getKeyboardLeft() const { return kbLeft; }
        [[nodiscard]] Qt::Key getKeyboardRight() const { return kbRight; }
        [[nodiscard]] Qt::Key getKeyboardFastLeft() const { return kbFastLeft; }
        [[nodiscard]] Qt::Key getKeyboardFastRight() const { return kbFastRight; }
        [[nodiscard]] Qt::Key getKeyboardAction() const { return kbAction; }
        [[nodiscard]] Qt::Key getKeyboardBack() const { return kbBack; }
        [[nodiscard]] Qt::Key getKeyboardScrollUp() const { return kbScrollUp; }
        [[nodiscard]] Qt::Key getKeyboardScrollDown() const { return kbScrollDown; }
        [[nodiscard]] Qt::Key getKeyboardScrollTop() const { return kbScrollTop; }
        [[nodiscard]] Qt::Key getKeyboardScrollBottom() const { return kbScrollBottom; }
        [[nodiscard]] Qt::Key getKeyboardInputMode() const { return kbInputMode; }
        void setCloseToTray(const bool enable) { closeToTray = enable; }
        void setRememberWindowState(const bool enable) { rememberWindowState = enable; }
        void setRunAtStartup(const bool enable) { runAtStartup = enable; }
        void setTheme(const Style::StyleType type) { styleType = type; }
        void setKeyboardNavbarUp(const Qt::Key key) { kbNavbarUp = key; }
        void setKeyboardNavbarDown(const Qt::Key key) { kbNavbarDown = key; }
        void setKeyboardRefresh(const Qt::Key key) { kbRefresh = key; }
        void setKeyboardApply(const Qt::Key key) { kbApply = key; }
        void setKeyboardUp(const Qt::Key key) { kbUp = key; }
        void setKeyboardDown(const Qt::Key key) { kbDown = key; }
        void setKeyboardLeft(const Qt::Key key) { kbLeft = key; }
        void setKeyboardRight(const Qt::Key key) { kbRight = key; }
        void setKeyboardFastLeft(const Qt::Key key) { kbFastLeft = key; }
        void setKeyboardFastRight(const Qt::Key key) { kbFastRight = key; }
        void setKeyboardAction(const Qt::Key key) { kbAction = key; }
        void setKeyboardBack(const Qt::Key key) { kbBack = key; }
        void setKeyboardScrollUp(const Qt::Key key) { kbScrollUp = key; }
        void setKeyboardScrollDown(const Qt::Key key) { kbScrollDown = key; }
        void setKeyboardScrollTop(const Qt::Key key) { kbScrollTop = key; }
        void setKeyboardScrollBottom(const Qt::Key key) { kbScrollBottom = key; }
        void setKeyboardInputMode(const Qt::Key key) { kbInputMode = key; }

        [[nodiscard]] static Settings &get();
        void setPath(const QString &diskPath);
        [[nodiscard]] bool load();
        [[nodiscard]] bool save() const;
    };
}