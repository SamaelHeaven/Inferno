#include "Color.h"

#include "../core/file.h"

namespace inferno {
    const Color Color::WHITE{255, 255, 255};
    const Color Color::BLACK{0, 0, 0};
    const Color Color::TRANSPARENT{0, 0, 0, 0};
    const Color Color::LIGHT_GRAY{200, 200, 200};
    const Color Color::GRAY{130, 130, 130};
    const Color Color::DARK_GRAY{80, 80, 80};
    const Color Color::YELLOW{253, 249, 0};
    const Color Color::GOLD{255, 203, 0};
    const Color Color::ORANGE{255, 161, 0};
    const Color Color::PINK{255, 109, 194};
    const Color Color::RED{230, 41, 55};
    const Color Color::MAROON{190, 33, 55};
    const Color Color::GREEN{0, 228, 48};
    const Color Color::LIME{0, 158, 47};
    const Color Color::DARK_GREEN{0, 117, 44};
    const Color Color::SKY_BLUE{102, 191, 255};
    const Color Color::BLUE{0, 121, 241};
    const Color Color::DARK_BLUE{0, 82, 172};
    const Color Color::PURPLE{200, 122, 255};
    const Color Color::VIOLET{135, 60, 190};
    const Color Color::DARK_PURPLE{112, 31, 126};
    const Color Color::BEIGE{211, 176, 131};
    const Color Color::BROWN{127, 106, 79};
    const Color Color::DARK_BROWN{76, 63, 47};

    Color::Color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    Color::Color(std::string hexadecimal) {
        try {
            while (hexadecimal[0] == '#') {
                hexadecimal = hexadecimal.substr(1);
            }
            this->red = std::stoul(hexadecimal.substr(0, 2), nullptr, 16);
            this->green = std::stoul(hexadecimal.substr(2, 2), nullptr, 16);
            this->blue = std::stoul(hexadecimal.substr(4, 2), nullptr, 16);
            this->alpha = hexadecimal.length() == 9 ? std::stoul(hexadecimal.substr(6, 2), nullptr, 16) : 255;
        } catch (const std::exception &_) {
            throw std::invalid_argument("Invalid hexadecimal color code: \"" + hexadecimal + "\"");
        }
    }

    Color::Color(const char *hexadecimal) : Color(std::string(hexadecimal)) {}

    std::string Color::to_string() const {
        return "{ red: " + std::to_string(red) + ", green: " + std::to_string(green) +
            ", blue: " + std::to_string(blue) + ", alpha: " + std::to_string(alpha) + " }";
    }

    bool Color::operator==(const Color &other) const {
        return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha;
    }
}
