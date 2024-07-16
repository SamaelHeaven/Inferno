#include "Vector2.h"

namespace inferno {
    Vector2::Vector2() : x(0), y(0) {}

    Vector2::Vector2(const float xy) : x(xy), y(xy) {}

    Vector2::Vector2(const float x, const float y) : x(x), y(y) {}
}
