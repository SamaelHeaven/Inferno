#include "Vector2.h"

namespace inferno {
    const Vector2 Vector2::ZERO = Vector2(0);
    const Vector2 Vector2::UP = Vector2(0, -1);
    const Vector2 Vector2::DOWN = Vector2(0, 1);
    const Vector2 Vector2::LEFT = Vector2(-1, 0);
    const Vector2 Vector2::RIGHT = Vector2(1, 0);

    Vector2::Vector2(const float xy) : x(xy), y(xy) {}

    Vector2::Vector2(const float x, const float y) : x(x), y(y) {}
}
