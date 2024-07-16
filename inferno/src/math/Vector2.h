#pragma once

namespace inferno {
    struct Vector2 final {
        const static Vector2 ZERO;
        const static Vector2 UP;
        const static Vector2 DOWN;
        const static Vector2 LEFT;
        const static Vector2 RIGHT;

        const float x;
        const float y;

        explicit Vector2(float xy);

        Vector2(float x, float y);
    };
}
