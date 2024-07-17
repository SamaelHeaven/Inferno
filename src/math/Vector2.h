#pragma once

namespace inferno {
    struct Vector2 final {
        const static Vector2 ZERO;
        const static Vector2 UP;
        const static Vector2 DOWN;
        const static Vector2 LEFT;
        const static Vector2 RIGHT;

        float x;
        float y;

        explicit Vector2(float xy);

        Vector2(float x, float y);

        bool operator==(const Vector2 &other) const;

        Vector2 operator+(const Vector2 &other) const;

        Vector2 operator-(const Vector2 &other) const;

        Vector2 operator*(const Vector2 &other) const;

        Vector2 operator/(const Vector2 &other) const;

        Vector2 &operator+=(const Vector2 &other);

        Vector2 &operator-=(const Vector2 &other);

        Vector2 &operator*=(const Vector2 &other);

        Vector2 &operator/=(const Vector2 &other);

        bool operator==(float xy) const;

        Vector2 operator+(float xy) const;

        Vector2 operator-(float xy) const;

        Vector2 operator*(float xy) const;

        Vector2 operator/(float xy) const;

        Vector2 &operator+=(float xy);

        Vector2 &operator-=(float xy);

        Vector2 &operator*=(float xy);

        Vector2 &operator/=(float xy);
    };
}
