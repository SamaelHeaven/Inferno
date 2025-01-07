#pragma once

#include "../inferno.h"

namespace inferno {
    struct Vector2 {
        const static Vector2 ZERO;
        const static Vector2 UP;
        const static Vector2 DOWN;
        const static Vector2 LEFT;
        const static Vector2 RIGHT;

        float x;
        float y;

        Vector2();

        // ReSharper disable once CppNonExplicitConvertingConstructor
        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2(const T xy) { // NOLINT(*-explicit-constructor)
            x = static_cast<float>(xy);
            y = static_cast<float>(xy);
        }

        template <typename X, typename Y, std::enable_if_t<std::is_arithmetic_v<X>> * = nullptr,
            std::enable_if<std::is_arithmetic_v<Y>> * = nullptr>
        Vector2(const X x, const Y y) {
            this->x = static_cast<float>(x);
            this->y = static_cast<float>(y);
        }

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

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 operator+(const T t) const {
            return *this + static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 operator-(const T t) const {
            return *this - static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 operator*(const T t) const {
            return *this * static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 operator/(const T t) const {
            return *this / static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 &operator+=(const T t) {
            return *this += static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 &operator-=(const T t) {
            return *this -= static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 &operator*=(const T t) {
            return *this *= static_cast<float>(t);
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr> Vector2 &operator/=(const T t) {
            return *this /= static_cast<float>(t);
        }

        [[nodiscard]] std::string to_string() const;

        [[nodiscard]] Vector2 clamp(Vector2 min, Vector2 max) const;

        [[nodiscard]] Vector2 clamp(float min, float max) const;

        [[nodiscard]] Vector2 clamp_x(float min, float max) const;

        [[nodiscard]] Vector2 clamp_y(float min, float max) const;

        template <typename Min, typename Max, std::enable_if_t<std::is_arithmetic_v<Min>> * = nullptr,
            std::enable_if<std::is_arithmetic_v<Max>> * = nullptr>
        [[nodiscard]] Vector2 clamp(const Min min, const Max max) const {
            return clamp(static_cast<float>(min), static_cast<float>(max));
        }

        template <typename Min, typename Max, std::enable_if_t<std::is_arithmetic_v<Min>> * = nullptr,
            std::enable_if<std::is_arithmetic_v<Max>> * = nullptr>
        [[nodiscard]] Vector2 clamp_x(const Min min, const Max max) const {
            return clamp_x(static_cast<float>(min), static_cast<float>(max));
        }

        template <typename Min, typename Max, std::enable_if_t<std::is_arithmetic_v<Min>> * = nullptr,
            std::enable_if<std::is_arithmetic_v<Max>> * = nullptr>
        [[nodiscard]] Vector2 clamp_y(const Min min, const Max max) const {
            return clamp_y(static_cast<float>(min), static_cast<float>(max));
        }

        [[nodiscard]] float distance_to(Vector2 v) const;

        [[nodiscard]] float dot(Vector2 v) const;

        [[nodiscard]] float cross(Vector2 v) const;

        [[nodiscard]] Vector2 rotate(float degrees, Vector2 v) const;

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr>
        [[nodiscard]] Vector2 rotate(const T degrees, const Vector2 v) const {
            return rotate(static_cast<float>(degrees), v);
        }

        [[nodiscard]] float length() const;

        [[nodiscard]] float angle_between(Vector2 v) const;

        [[nodiscard]] Vector2 reflect(Vector2 v) const;

        [[nodiscard]] Vector2 lerp(Vector2 end, float t) const;

        [[nodiscard]] Vector2 slerp(Vector2 end, float t) const;

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr>
        [[nodiscard]] Vector2 lerp(const Vector2 end, const T t) const {
            return lerp(end, static_cast<float>(t));
        }

        template <typename T, std::enable_if<std::is_arithmetic_v<T>> * = nullptr>
        [[nodiscard]] Vector2 slerp(const Vector2 end, const T t) const {
            return slerp(end, static_cast<float>(t));
        }

        [[nodiscard]] Vector2 round() const;

        [[nodiscard]] Vector2 abs() const;

        [[nodiscard]] Vector2 normalize() const;

        [[nodiscard]] float modifier_x() const;

        [[nodiscard]] float modifier_y() const;

        [[nodiscard]] Vector2 modifiers() const;
    };
}
