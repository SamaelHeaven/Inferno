#pragma once

#include "../inferno.h"

namespace inferno {
    struct Vector2 final {
        const static Vector2 ZERO;
        const static Vector2 UP;
        const static Vector2 DOWN;
        const static Vector2 LEFT;
        const static Vector2 RIGHT;

        float x;
        float y;

        Vector2();

        explicit Vector2(float xy);

        Vector2(float x, float y);

        bool operator==(Vector2 other) const;

        Vector2 operator+(Vector2 v) const;

        Vector2 operator-(Vector2 v) const;

        Vector2 operator*(Vector2 v) const;

        Vector2 operator/(Vector2 v) const;

        Vector2 &operator+=(Vector2 v);

        Vector2 &operator-=(Vector2 v);

        Vector2 &operator*=(Vector2 v);

        Vector2 &operator/=(Vector2 v);

        Vector2 operator+(float f) const;

        Vector2 operator-(float f) const;

        Vector2 operator*(float f) const;

        Vector2 operator/(float f) const;

        Vector2 &operator+=(float f);

        Vector2 &operator-=(float f);

        Vector2 &operator*=(float f);

        Vector2 &operator/=(float f);

        [[nodiscard]] std::string to_string() const;

        [[nodiscard]] Vector2 clamp(Vector2 min, Vector2 max) const;

        [[nodiscard]] Vector2 clamp(float min, float max) const;

        [[nodiscard]] Vector2 clamp_x(float min, float max) const;

        [[nodiscard]] Vector2 clamp_y(float min, float max) const;

        [[nodiscard]] float distance_to(Vector2 v) const;

        [[nodiscard]] float dot(Vector2 v) const;

        [[nodiscard]] float cross(Vector2 v) const;

        [[nodiscard]] Vector2 rotate(float degrees, Vector2 v) const;

        [[nodiscard]] float length() const;

        [[nodiscard]] float angle_between(Vector2 v) const;

        [[nodiscard]] Vector2 reflect(Vector2 v) const;

        [[nodiscard]] Vector2 lerp(Vector2 end, float t) const;

        [[nodiscard]] Vector2 slerp(Vector2 end, float t) const;

        [[nodiscard]] Vector2 round() const;

        [[nodiscard]] Vector2 abs() const;

        [[nodiscard]] Vector2 normalize() const;

        [[nodiscard]] float modifier_x() const;

        [[nodiscard]] float modifier_y() const;

        [[nodiscard]] Vector2 modifiers() const;
    };
}
