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
#include "Style.h"

namespace PWT::Style {
    class VoidPurpleStyle final: public Style {
    private:
        static constexpr QColor voidPurple = hexToQ("16001F");
        static constexpr QColor deeperPurple = hexToQ("0A0116", "AA");
        static constexpr QColor winePurple = hexToQ("40063E", "C8");
        static constexpr QColor petrolBlue = hexToQ("39C6E9");
        static constexpr QColor iceWhite = hexToQ("E1E7F5");
        static constexpr QColor slateBlue = hexToQ("717D96");
        static constexpr QColor neonMagenta = hexToQ("FF2DFF");
        static constexpr QColor softNeonMagenta = hexToQ("FF2DFF", "96");
        static constexpr QColor roseRed = hexToQ("EA3F57");
        static constexpr QColor neonGreen = hexToQ("4DFFB8");
        static constexpr QColor electricMagenta = hexToQ("FF2DFF");
        static constexpr QColor electricViolet = hexToQ("A855FF");
        static constexpr QColor deepPlum = hexToQ("4A145C");
        static constexpr QColor white = hexToQ("ffffff");

    public:
        ~VoidPurpleStyle() override = default;

        [[nodiscard]] const QColor &mainWindowText() const override { return iceWhite; }
        [[nodiscard]] const QColor &mainWindowBackground() const override { return voidPurple; }
        [[nodiscard]] std::string_view linkText() const override { return "#F9FAF5"; }
        [[nodiscard]] const QColor &switchButtonTrack() const override { return deeperPurple; }
        [[nodiscard]] const QColor &switchButtonTrackBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &switchButtonTrackActive() const override { return roseRed; }
        [[nodiscard]] const QColor &switchButtonTrackActiveBorder() const override { return deeperPurple; }
        [[nodiscard]] const QColor &switchButtonThumb() const override { return iceWhite; }
        [[nodiscard]] const QColor &switchButtonThumbBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &sliderTrack() const override { return deeperPurple; }
        [[nodiscard]] const QColor &sliderTrackBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &sliderTrackActive() const override { return roseRed; }
        [[nodiscard]] const QColor &sliderTrackActiveBorder() const override { return deeperPurple; }
        [[nodiscard]] const QColor &sliderThumb() const override { return iceWhite; }
        [[nodiscard]] const QColor &sliderThumbBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &button() const override { return deeperPurple; }
        [[nodiscard]] const QColor &buttonLabel() const override { return iceWhite; }
        [[nodiscard]] const QColor &buttonBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &buttonHovered() const override { return winePurple; }
        [[nodiscard]] const QColor &selectComboBox() const override { return deeperPurple; }
        [[nodiscard]] const QColor &selectComboBoxActive() const override { return winePurple; }
        [[nodiscard]] const QColor &selectComboBoxBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &selectComboBoxText() const override { return iceWhite; }
        [[nodiscard]] const QColor &selectComboBoxListItmSelected() const override { return winePurple; }
        [[nodiscard]] const QColor &textEdit() const override { return deeperPurple; }
        [[nodiscard]] const QColor &textEditBorder() const override { return slateBlue; }
        [[nodiscard]] const QColor &textEditActive() const override { return white; }
        [[nodiscard]] const QColor &textEditText() const override { return iceWhite; }
        [[nodiscard]] const QColor &navButtonIcon() const override { return iceWhite; }
        [[nodiscard]] const QColor &navButtonHovered() const override { return softNeonMagenta; }
        [[nodiscard]] const QColor &navButtonActive() const override { return neonMagenta; }
        [[nodiscard]] const QColor &scrollbar() const override { return softNeonMagenta; }
        [[nodiscard]] const QColor &statusReady() const override { return neonGreen; }
        [[nodiscard]] const QColor &focusBorder() const override { return electricMagenta; }
        [[nodiscard]] const QColor &focusBorderContrast() const override { return white; }
        [[nodiscard]] const QColor &titleBackground() const override { return electricViolet; }
        [[nodiscard]] const QColor &titleText() const override { return deepPlum; }
    };
}
