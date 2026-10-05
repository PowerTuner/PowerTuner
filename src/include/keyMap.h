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

namespace PWT {
    using namespace Qt::StringLiterals;

    static const QMap<Qt::Key, QString> KeyMap = {
        {Qt::Key_A, u"A"_s}, {Qt::Key_B, u"B"_s}, {Qt::Key_C, u"C"_s}, {Qt::Key_D, u"D"_s},
        {Qt::Key_E, u"E"_s}, {Qt::Key_F, u"F"_s}, {Qt::Key_G, u"G"_s}, {Qt::Key_H, u"H"_s},
        {Qt::Key_I, u"I"_s}, {Qt::Key_J, u"J"_s}, {Qt::Key_K, u"K"_s}, {Qt::Key_L, u"L"_s},
        {Qt::Key_M, u"M"_s}, {Qt::Key_N, u"N"_s}, {Qt::Key_O, u"O"_s}, {Qt::Key_P, u"P"_s},
        {Qt::Key_Q, u"Q"_s}, {Qt::Key_R, u"R"_s}, {Qt::Key_S, u"S"_s}, {Qt::Key_T, u"T"_s},
        {Qt::Key_U, u"U"_s}, {Qt::Key_V, u"V"_s}, {Qt::Key_W, u"W"_s}, {Qt::Key_X, u"X"_s},
        {Qt::Key_Y, u"Y"_s}, {Qt::Key_Z, u"Z"_s},

        {Qt::Key_0, u"0"_s}, {Qt::Key_1, u"1"_s}, {Qt::Key_2, u"2"_s}, {Qt::Key_3, u"3"_s},
        {Qt::Key_4, u"4"_s}, {Qt::Key_5, u"5"_s}, {Qt::Key_6, u"6"_s}, {Qt::Key_7, u"7"_s},
        {Qt::Key_8, u"8"_s}, {Qt::Key_9, u"9"_s},

        {Qt::Key_F1, u"F1"_s}, {Qt::Key_F2, u"F2"_s}, {Qt::Key_F3, u"F3"_s},
        {Qt::Key_F4, u"F4"_s}, {Qt::Key_F5, u"F5"_s}, {Qt::Key_F6, u"F6"_s},
        {Qt::Key_F7, u"F7"_s}, {Qt::Key_F8, u"F8"_s}, {Qt::Key_F9, u"F9"_s},
        {Qt::Key_F10, u"F10"_s}, {Qt::Key_F11, u"F11"_s}, {Qt::Key_F12, u"F12"_s},
        {Qt::Key_F13, u"F13"_s}, {Qt::Key_F14, u"F14"_s}, {Qt::Key_F15, u"F15"_s},
        {Qt::Key_F16, u"F16"_s}, {Qt::Key_F17, u"F17"_s}, {Qt::Key_F18, u"F18"_s},
        {Qt::Key_F19, u"F19"_s}, {Qt::Key_F20, u"F20"_s}, {Qt::Key_F21, u"F21"_s},
        {Qt::Key_F22, u"F22"_s}, {Qt::Key_F23, u"F23"_s}, {Qt::Key_F24, u"F24"_s},
        {Qt::Key_F25, u"F25"_s}, {Qt::Key_F26, u"F26"_s}, {Qt::Key_F27, u"F27"_s},
        {Qt::Key_F28, u"F28"_s}, {Qt::Key_F29, u"F29"_s}, {Qt::Key_F30, u"F30"_s},
        {Qt::Key_F31, u"F31"_s}, {Qt::Key_F32, u"F32"_s}, {Qt::Key_F33, u"F33"_s},
        {Qt::Key_F34, u"F34"_s}, {Qt::Key_F35, u"F35"_s},

        {Qt::Key_Escape, u"Escape"_s},
        {Qt::Key_Tab, u"Tab"_s},
        {Qt::Key_Backtab, u"Backtab"_s},
        {Qt::Key_Backspace, u"Backspace"_s},
        {Qt::Key_Return, u"Return"_s},
        {Qt::Key_Space, u"Space"_s},
        {Qt::Key_Enter, u"Enter"_s},
        {Qt::Key_Insert, u"Insert"_s},
        {Qt::Key_Delete, u"Delete"_s},
        {Qt::Key_Pause, u"Pause"_s},
        {Qt::Key_Print, u"Print"_s},
        {Qt::Key_Clear, u"Clear"_s},

        {Qt::Key_Home, u"Home"_s},
        {Qt::Key_End, u"End"_s},
        {Qt::Key_Up, u"Up Arrow"_s},
        {Qt::Key_Down, u"Down Arrow"_s},
        {Qt::Key_Left, u"Left Arrow"_s},
        {Qt::Key_Right, u"Right Arrow"_s},
        {Qt::Key_PageUp, u"Page Up"_s},
        {Qt::Key_PageDown, u"Page Down"_s},
        {Qt::Key_Shift, u"Shift"_s},
        {Qt::Key_Control, u"Control"_s},
        {Qt::Key_Meta, u"Meta/Windows"_s},
        {Qt::Key_Alt, u"Alt"_s},
        {Qt::Key_AltGr, u"AltGr"_s},

        {Qt::Key_MediaPlay, u"Media Play"_s},
        {Qt::Key_MediaStop, u"Media Stop"_s},
        {Qt::Key_MediaPrevious, u"Media Previous"_s},
        {Qt::Key_MediaNext, u"Media Next"_s},

        {Qt::Key_Plus, u"+"_s},
        {Qt::Key_Minus, u"-"_s},
        {Qt::Key_Period, u"."_s},
        {Qt::Key_Colon, u":"_s},
        {Qt::Key_Semicolon, u";"_s},
        {Qt::Key_Less, u"<"_s},
        {Qt::Key_Equal, u"="_s},
        {Qt::Key_Greater, u">"_s},
        {Qt::Key_Question, u"?"_s},
        {Qt::Key_At, u"@"_s},
        {Qt::Key_BracketLeft, u"["_s},
        {Qt::Key_BracketRight, u"]"_s},
        {Qt::Key_AsciiCircum, u"^"_s},
        {Qt::Key_BraceLeft, u"{"_s},
        {Qt::Key_BraceRight, u"}"_s},
        {Qt::Key_Bar, u"|"_s},
        {Qt::Key_AsciiTilde, u"~"_s}
    };
}