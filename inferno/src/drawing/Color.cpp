#include "Color.h"

#include "../core/file.h"

namespace inferno {
    Color Color::WHITE = Color(255, 255, 255);
    Color Color::BLACK = Color(0, 0, 0);
    Color Color::TRANSPARENT = Color(0, 0, 0, 0);
    Color Color::LIGHT_GRAY = Color(200, 200, 200);
    Color Color::GRAY = Color(130, 130, 130);
    Color Color::DARK_GRAY = Color(80, 80, 80);
    Color Color::YELLOW = Color(253, 249, 0);
    Color Color::GOLD = Color(255, 203, 0);
    Color Color::ORANGE = Color(255, 161, 0);
    Color Color::PINK = Color(255, 109, 194);
    Color Color::RED = Color(230, 41, 55);
    Color Color::MAROON = Color(190, 33, 55);
    Color Color::GREEN = Color(0, 228, 48);
    Color Color::LIME = Color(0, 158, 47);
    Color Color::DARK_GREEN = Color(0, 117, 44);
    Color Color::SKY_BLUE = Color(102, 191, 255);
    Color Color::BLUE = Color(0, 121, 241);
    Color Color::DARK_BLUE = Color(0, 82, 172);
    Color Color::PURPLE = Color(200, 122, 255);
    Color Color::VIOLET = Color(135, 60, 190);
    Color Color::DARK_PURPLE = Color(112, 31, 126);
    Color Color::BEIGE = Color(211, 176, 131);
    Color Color::BROWN = Color(127, 106, 79);
    Color Color::DARK_BROWN = Color(76, 63, 47);

    Color::Color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) {
        _color = internal::Color(red, green, blue, alpha);
    }

    Color::Color(std::string hexadecimal) {
        try {
            while (hexadecimal[0] == '#') {
                hexadecimal = hexadecimal.substr(1);
            }
            const auto red = std::stoul(hexadecimal.substr(0, 2), nullptr, 16);
            const auto green = std::stoul(hexadecimal.substr(2, 2), nullptr, 16);
            const auto blue = std::stoul(hexadecimal.substr(4, 2), nullptr, 16);
            const auto alpha = hexadecimal.length() == 9 ? std::stoul(hexadecimal.substr(6, 2), nullptr, 16) : 255;
            _color = internal::Color(red, green, blue, alpha);
        } catch (const std::exception &_) {
            throw std::invalid_argument("Invalid hexadecimal color code: \"" + hexadecimal + "\"");
        }
    }

    uint8_t Color::get_red() const {
        return _color.r;
    }

    uint8_t Color::get_green() const {
        return _color.g;
    }

    uint8_t Color::get_blue() const {
        return _color.b;
    }

    uint8_t Color::get_alpha() const {
        return _color.a;
    }

    bool Color::operator==(const Color &other) const {
        return get_red() == other.get_red() && get_green() == other.get_green() &&
               get_blue() == other.get_blue() && get_alpha() == other.get_alpha();
    }
}
