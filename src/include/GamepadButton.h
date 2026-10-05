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

namespace PWT {
    enum class GamepadButton: int {
        None,
        SOUTH,
        EAST,
        WEST,
        NORTH,
        DPAD_UP,
        DPAD_DOWN,
        DPAD_LEFT,
        DPAD_RIGHT,
        SELECT,
        START,
        HOME,
        MISC,
        UP_LEFT_PADDLE,
        LOW_LEFT_PADDLE,
        UP_RIGHT_PADDLE,
        LOW_RIGHT_PADDLE,
        L1,
        L2,
        L3,
        R1,
        R2,
        R3,
        ANALOG_LEFT_UP,
        ANALOG_LEFT_DOWN,
        ANALOG_LEFT_LEFT,
        ANALOG_LEFT_RIGHT,
        ANALOG_RIGHT_UP,
        ANALOG_RIGHT_DOWN,
        ANALOG_RIGHT_LEFT,
        ANALOG_RIGHT_RIGHT,
        APP_COMBO
    };
}
