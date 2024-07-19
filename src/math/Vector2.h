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

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        explicit Vector2(const T xy) {
            x = static_cast<float>(xy);
            y = static_cast<float>(xy);
        }

        template<typename TX, typename TY, std::enable_if_t<std::is_arithmetic_v<TX> > * = nullptr, std::enable_if<
            std::is_arithmetic_v<TY> >* = nullptr>
        Vector2(const TX x, const TY y) {
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

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 operator+(const T t) const {
            return *this + static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 operator-(const T t) const {
            return *this - static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 operator*(const T t) const {
            return *this * static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 operator/(const T t) const {
            return *this / static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 &operator+=(const T t) {
            return *this += static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 &operator-=(const T t) {
            return *this -= static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 &operator*=(const T t) {
            return *this *= static_cast<float>(t);
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        Vector2 &operator/=(const T t) {
            return *this /= static_cast<float>(t);
        }

        [[nodiscard]] std::string to_string() const;

        [[nodiscard]] Vector2 clamp(Vector2 min, Vector2 max) const;

        [[nodiscard]] Vector2 clamp(float min, float max) const;

        [[nodiscard]] Vector2 clamp_x(float min, float max) const;

        [[nodiscard]] Vector2 clamp_y(float min, float max) const;

        template<typename TMIN, typename TMAX, std::enable_if_t<std::is_arithmetic_v<TMIN> > * = nullptr, std::enable_if
            <std::is_arithmetic_v<TMAX> >* = nullptr>
        [[nodiscard]] Vector2 clamp(const TMIN min, const TMAX max) const {
            return clamp(static_cast<float>(min), static_cast<float>(max));
        }

        template<typename TMIN, typename TMAX, std::enable_if_t<std::is_arithmetic_v<TMIN> > * = nullptr, std::enable_if
            <std::is_arithmetic_v<TMAX> >* = nullptr>
        [[nodiscard]] Vector2 clamp_x(const TMIN min, const TMAX max) const {
            return clamp_x(static_cast<float>(min), static_cast<float>(max));
        }

        template<typename TMIN, typename TMAX, std::enable_if_t<std::is_arithmetic_v<TMIN> > * = nullptr, std::enable_if
            <std::is_arithmetic_v<TMAX> >* = nullptr>
        [[nodiscard]] Vector2 clamp_y(const TMIN min, const TMAX max) const {
            return clamp_y(static_cast<float>(min), static_cast<float>(max));
        }

        [[nodiscard]] float distance_to(Vector2 v) const;

        [[nodiscard]] float dot(Vector2 v) const;

        [[nodiscard]] float cross(Vector2 v) const;

        [[nodiscard]] Vector2 rotate(float degrees, Vector2 v) const;

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        [[nodiscard]] Vector2 rotate(const T degrees, const Vector2 v) const {
            return rotate(static_cast<float>(degrees), v);
        }

        [[nodiscard]] float length() const;

        [[nodiscard]] float angle_between(Vector2 v) const;

        [[nodiscard]] Vector2 reflect(Vector2 v) const;

        [[nodiscard]] Vector2 lerp(Vector2 end, float t) const;

        [[nodiscard]] Vector2 slerp(Vector2 end, float t) const;

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
        [[nodiscard]] Vector2 lerp(const Vector2 end, const T t) const {
            return lerp(end, static_cast<float>(t));
        }

        template<typename T, std::enable_if<std::is_arithmetic_v<T> >* = nullptr>
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
