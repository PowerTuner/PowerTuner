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
#include <QColor>

namespace PWT::Style {
    class Style {
    private:
        [[nodiscard]]
        static consteval int hexToI(const char c) {
            if (c >= '0' && c <= '9')
                return c - '0';
            else if (c >= 'A' && c <= 'F')
                return c - 'A' + 10;
            else if (c >= 'a' && c <= 'f')
                return c - 'a' + 10;

            throw "invalid hex char";
        }

    protected:
        [[nodiscard]]
        static consteval QColor hexToQ(const std::string_view rgb, const std::string_view alpha = "ff") {
            if (rgb.size() > 6 || alpha.size() > 2)
                throw "invalid rgb string";

            return {
                (hexToI(rgb[0]) << 4) | hexToI(rgb[1]),
                (hexToI(rgb[2]) << 4) | hexToI(rgb[3]),
                (hexToI(rgb[4]) << 4) | hexToI(rgb[5]),
                (hexToI(alpha[0]) << 4) | hexToI(alpha[1])
            };
        }

    public:
        virtual ~Style() = default;

        [[nodiscard]] virtual const QColor &mainWindowText() const = 0;
        [[nodiscard]] virtual const QColor &mainWindowBackground() const = 0;
        [[nodiscard]] virtual std::string_view linkText() const = 0;
        [[nodiscard]] virtual const QColor &switchButtonTrack() const = 0;
        [[nodiscard]] virtual const QColor &switchButtonTrackBorder() const = 0;
        [[nodiscard]] virtual const QColor &switchButtonTrackActive() const = 0;
        [[nodiscard]] virtual const QColor &switchButtonTrackActiveBorder() const = 0;
        [[nodiscard]] virtual const QColor &switchButtonThumb() const = 0;
        [[nodiscard]] virtual const QColor &switchButtonThumbBorder() const = 0;
        [[nodiscard]] virtual const QColor &sliderTrack() const = 0;
        [[nodiscard]] virtual const QColor &sliderTrackBorder() const = 0;
        [[nodiscard]] virtual const QColor &sliderTrackActive() const = 0;
        [[nodiscard]] virtual const QColor &sliderTrackActiveBorder() const = 0;
        [[nodiscard]] virtual const QColor &sliderThumb() const = 0;
        [[nodiscard]] virtual const QColor &sliderThumbBorder() const = 0;
        [[nodiscard]] virtual const QColor &button() const = 0;
        [[nodiscard]] virtual const QColor &buttonLabel() const = 0;
        [[nodiscard]] virtual const QColor &buttonBorder() const = 0;
        [[nodiscard]] virtual const QColor &buttonHovered() const = 0;
        [[nodiscard]] virtual const QColor &selectComboBox() const = 0;
        [[nodiscard]] virtual const QColor &selectComboBoxBorder() const = 0;
        [[nodiscard]] virtual const QColor &selectComboBoxText() const = 0;
        [[nodiscard]] virtual const QColor &selectComboBoxActive() const = 0;
        [[nodiscard]] virtual const QColor &selectComboBoxListItmSelected() const = 0;
        [[nodiscard]] virtual const QColor &textEdit() const = 0;
        [[nodiscard]] virtual const QColor &textEditBorder() const = 0;
        [[nodiscard]] virtual const QColor &textEditText() const = 0;
        [[nodiscard]] virtual const QColor &navButtonIcon() const = 0;
        [[nodiscard]] virtual const QColor &navButtonHovered() const = 0;
        [[nodiscard]] virtual const QColor &navButtonActive() const = 0;
        [[nodiscard]] virtual const QColor &scrollbar() const = 0;
        [[nodiscard]] virtual const QColor &statusReady() const = 0;
        [[nodiscard]] virtual const QColor &focusBorder() const = 0;
        [[nodiscard]] virtual const QColor &focusBorderContrast() const = 0;
        [[nodiscard]] virtual const QColor &titleBackground() const = 0;
        [[nodiscard]] virtual const QColor &titleText() const = 0;
    };
}