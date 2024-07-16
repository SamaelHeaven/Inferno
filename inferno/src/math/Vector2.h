#pragma once

namespace inferno {
    struct Vector2 final {
        const float x;
        const float y;

        Vector2();

        explicit Vector2(float xy);

        Vector2(float x, float y);
    };
}
