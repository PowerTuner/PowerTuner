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
#include <QMap>

#include "GamepadButton.h"

namespace PWT {
    using namespace Qt::StringLiterals;

    static const QMap<GamepadButton, QString> GamepadButtonMap = {
        {GamepadButton::SOUTH, u"A / B / X"_s},
        {GamepadButton::EAST, u"B / A / \u25cb"_s},
        {GamepadButton::WEST, u"X / Y / \u25a1"_s},
        {GamepadButton::NORTH, u"Y / X / \u25b3"_s},
        {GamepadButton::DPAD_UP, u"D-Pad Up"_s},
        {GamepadButton::DPAD_DOWN, u"D-Pad Down"_s},
        {GamepadButton::DPAD_LEFT, u"D-Pad Left"_s},
        {GamepadButton::DPAD_RIGHT, u"D-Pad Right"_s},
        {GamepadButton::SELECT, u"Select"_s},
        {GamepadButton::START, u"Start"_s},
        {GamepadButton::HOME, u"Menu"_s},
        {GamepadButton::MISC, u"Share / Capture / Mic."_s},
        {GamepadButton::L1, u"L1"_s},
        {GamepadButton::L2, u"L2"_s},
        {GamepadButton::L3, u"L3"_s},
        {GamepadButton::R1, u"R1"_s},
        {GamepadButton::R2, u"R2"_s},
        {GamepadButton::R3, u"R3"_s},
        {GamepadButton::UP_LEFT_PADDLE, u"Upper Left Paddle / L4"_s},
        {GamepadButton::LOW_LEFT_PADDLE, u"Lower Left Paddle / L5"_s},
        {GamepadButton::UP_RIGHT_PADDLE, u"Upper Right Paddle / R4"_s},
        {GamepadButton::LOW_RIGHT_PADDLE, u"Lower Right Paddle / R5"_s},
        {GamepadButton::ANALOG_LEFT_UP, u"Left Stick Up"_s},
        {GamepadButton::ANALOG_LEFT_DOWN, u"Left Stick Down"_s},
        {GamepadButton::ANALOG_LEFT_LEFT, u"Left Stick Left"_s},
        {GamepadButton::ANALOG_LEFT_RIGHT, u"Left Stick Right"_s},
        {GamepadButton::ANALOG_RIGHT_UP, u"Right Stick Up"_s},
        {GamepadButton::ANALOG_RIGHT_DOWN, u"Right Stick Down"_s},
        {GamepadButton::ANALOG_RIGHT_LEFT, u"Right Stick Left"_s},
        {GamepadButton::ANALOG_RIGHT_RIGHT, u"Right Stick Right"_s}
    };

    static const QMap<GamepadButton, QString> GamepadButtonComboMap = {
        {GamepadButton::SOUTH, u"A / B / X"_s},
        {GamepadButton::EAST, u"B / A / \u25cb"_s},
        {GamepadButton::WEST, u"X / Y / \u25a1"_s},
        {GamepadButton::NORTH, u"Y / X / \u25b3"_s},
        {GamepadButton::DPAD_UP, u"D-Pad Up"_s},
        {GamepadButton::DPAD_DOWN, u"D-Pad Down"_s},
        {GamepadButton::DPAD_LEFT, u"D-Pad Left"_s},
        {GamepadButton::DPAD_RIGHT, u"D-Pad Right"_s},
        {GamepadButton::SELECT, u"Select"_s},
        {GamepadButton::START, u"Start"_s},
        {GamepadButton::HOME, u"Menu"_s},
        {GamepadButton::MISC, u"Share / Capture / Mic."_s},
        {GamepadButton::L1, u"L1"_s},
        {GamepadButton::L2, u"L2"_s},
        {GamepadButton::L3, u"L3"_s},
        {GamepadButton::R1, u"R1"_s},
        {GamepadButton::R2, u"R2"_s},
        {GamepadButton::R3, u"R3"_s},
        {GamepadButton::UP_LEFT_PADDLE, u"Upper Left Paddle / L4"_s},
        {GamepadButton::LOW_LEFT_PADDLE, u"Lower Left Paddle / L5"_s},
        {GamepadButton::UP_RIGHT_PADDLE, u"Upper Right Paddle / R4"_s},
        {GamepadButton::LOW_RIGHT_PADDLE, u"Lower Right Paddle / R5"_s},
    };
}