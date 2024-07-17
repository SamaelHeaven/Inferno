#include "./Vector2.h"

namespace inferno {
    const Vector2 Vector2::ZERO = Vector2(0);
    const Vector2 Vector2::UP = Vector2(0, -1);
    const Vector2 Vector2::DOWN = Vector2(0, 1);
    const Vector2 Vector2::LEFT = Vector2(-1, 0);
    const Vector2 Vector2::RIGHT = Vector2(1, 0);

    Vector2::Vector2(const float xy) : x(xy), y(xy) {}

    Vector2::Vector2(const float x, const float y) : x(x), y(y) {}

    bool Vector2::operator==(const Vector2 &other) const {
        return x == other.x && y == other.y;
    }

    Vector2 Vector2::operator+(const Vector2 &other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 Vector2::operator-(const Vector2 &other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 Vector2::operator*(const Vector2 &other) const {
        return {x * other.x, y * other.y};
    }

    Vector2 Vector2::operator/(const Vector2 &other) const {
        const auto x = other.x == 0 ? 0 : this->x / other.x;
        const auto y = other.y == 0 ? 0 : this->y / other.y;
        return {x, y};
    }

    bool Vector2::operator==(const float xy) const {
        return x == xy && y == xy;
    }

    Vector2 Vector2::operator+(const float xy) const {
        return {x + xy, y + xy};
    }

    Vector2 Vector2::operator-(const float xy) const {
        return {x - xy, y - xy};
    }

    Vector2 Vector2::operator*(const float xy) const {
        return {x * xy, y * xy};
    }

    Vector2 Vector2::operator/(const float xy) const {
        const auto x = xy == 0 ? 0 : this->x / xy;
        const auto y = xy == 0 ? 0 : this->y / xy;
        return {x, y};
    }
}
