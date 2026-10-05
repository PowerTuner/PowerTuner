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
#include "GamepadButton.h"

namespace PWT {
    struct GamepadMapping final {
        GamepadButton navbarUp = GamepadButton::L1;
        GamepadButton navbarDown = GamepadButton::R1;
        GamepadButton refresh = GamepadButton::START;
        GamepadButton apply = GamepadButton::SELECT;
        GamepadButton up = GamepadButton::DPAD_UP;
        GamepadButton down = GamepadButton::DPAD_DOWN;
        GamepadButton left = GamepadButton::DPAD_LEFT;
        GamepadButton right = GamepadButton::DPAD_RIGHT;
        GamepadButton fastLeft = GamepadButton::L2;
        GamepadButton fastRight = GamepadButton::R2;
        GamepadButton action = GamepadButton::SOUTH;
        GamepadButton back = GamepadButton::EAST;
        GamepadButton scrollUp = GamepadButton::ANALOG_RIGHT_UP;
        GamepadButton scrollDown = GamepadButton::ANALOG_RIGHT_DOWN;
        GamepadButton scrollTop = GamepadButton::ANALOG_RIGHT_LEFT;
        GamepadButton scrollBottom = GamepadButton::ANALOG_RIGHT_RIGHT;
        GamepadButton inputMode = GamepadButton::NORTH;
        GamepadButton appComboSlot1 = GamepadButton::L1;
        GamepadButton appComboSlot2 = GamepadButton::WEST;
        GamepadButton appComboSlot3 = GamepadButton::DPAD_DOWN;

        friend QDataStream &operator<<(QDataStream &ds, const GamepadMapping &data) {
            ds << data.navbarUp <<
                data.navbarDown <<
                data.left <<
                data.fastLeft <<
                data.right <<
                data.fastRight <<
                data.up <<
                data.down <<
                data.action <<
                data.back <<
                data.refresh <<
                data.apply <<
                data.inputMode <<
                data.scrollUp <<
                data.scrollDown <<
                data.scrollTop <<
                data.scrollBottom <<
                data.appComboSlot1 <<
                data.appComboSlot2 <<
                data.appComboSlot3;
            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, GamepadMapping &data) {
            ds >> data.navbarUp >>
                data.navbarDown >>
                data.left >>
                data.fastLeft >>
                data.right >>
                data.fastRight >>
                data.up >>
                data.down >>
                data.action >>
                data.back >>
                data.refresh >>
                data.apply >>
                data.inputMode >>
                data.scrollUp >>
                data.scrollDown >>
                data.scrollTop >>
                data.scrollBottom >>
                data.appComboSlot1 >>
                data.appComboSlot2 >>
                data.appComboSlot3;
            return ds;
        }
    };
}
