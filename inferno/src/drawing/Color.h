#pragma once

#include "../inferno.h"

namespace inferno {
    class Color final {
    public:
        static Color WHITE;
        static Color BLACK;
        static Color TRANSPARENT;
        static Color LIGHT_GRAY;
        static Color GRAY;
        static Color DARK_GRAY;
        static Color YELLOW;
        static Color GOLD;
        static Color ORANGE;
        static Color PINK;
        static Color RED;
        static Color MAROON;
        static Color GREEN;
        static Color LIME;
        static Color DARK_GREEN;
        static Color SKY_BLUE;
        static Color BLUE;
        static Color DARK_BLUE;
        static Color PURPLE;
        static Color VIOLET;
        static Color DARK_PURPLE;
        static Color BEIGE;
        static Color BROWN;
        static Color DARK_BROWN;

        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

        explicit Color(std::string hexadecimal);

        [[nodiscard]] uint8_t get_red() const;

        [[nodiscard]] uint8_t get_green() const;

        [[nodiscard]] uint8_t get_blue() const;

        [[nodiscard]] uint8_t get_alpha() const;

        bool operator==(const Color &other) const;

    private:
        internal::Color _color{};

        friend class Renderer;
    };
}
