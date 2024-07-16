#pragma once

#include "../inferno.h"

namespace inferno {
    class Color final {
    public:
        const static Color WHITE;
        const static Color BLACK;
        const static Color TRANSPARENT;
        const static Color LIGHT_GRAY;
        const static Color GRAY;
        const static Color DARK_GRAY;
        const static Color YELLOW;
        const static Color GOLD;
        const static Color ORANGE;
        const static Color PINK;
        const static Color RED;
        const static Color MAROON;
        const static Color GREEN;
        const static Color LIME;
        const static Color DARK_GREEN;
        const static Color SKY_BLUE;
        const static Color BLUE;
        const static Color DARK_BLUE;
        const static Color PURPLE;
        const static Color VIOLET;
        const static Color DARK_PURPLE;
        const static Color BEIGE;
        const static Color BROWN;
        const static Color DARK_BROWN;

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
