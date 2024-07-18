#include "./Vector2.h"

namespace inferno {
    const Vector2 Vector2::ZERO = Vector2();
    const Vector2 Vector2::UP = Vector2(0, -1);
    const Vector2 Vector2::DOWN = Vector2(0, 1);
    const Vector2 Vector2::LEFT = Vector2(-1, 0);
    const Vector2 Vector2::RIGHT = Vector2(1, 0);

    Vector2::Vector2() {
        x = 0;
        y = 0;
    }

    Vector2::Vector2(const float xy) {
        x = xy;
        y = xy;
    }

    Vector2::Vector2(const float x, const float y) {
        this->x = x;
        this->y = y;
    }

    bool Vector2::operator==(const Vector2 other) const {
        return x == other.x && y == other.y;
    }

    Vector2 Vector2::operator+(const Vector2 v) const {
        return {x + v.x, y + v.y};
    }

    Vector2 Vector2::operator-(const Vector2 v) const {
        return {x - v.x, y - v.y};
    }

    Vector2 Vector2::operator*(const Vector2 v) const {
        return {x * v.x, y * v.y};
    }

    Vector2 Vector2::operator/(const Vector2 v) const {
        const auto x = v.x == 0 ? 0 : this->x / v.x;
        const auto y = v.y == 0 ? 0 : this->y / v.y;
        return {x, y};
    }

    Vector2 &Vector2::operator+=(const Vector2 v) {
        *this = *this + v;
        return *this;
    }

    Vector2 &Vector2::operator-=(const Vector2 v) {
        *this = *this - v;
        return *this;
    }

    Vector2 &Vector2::operator*=(const Vector2 v) {
        *this = *this * v;
        return *this;
    }

    Vector2 &Vector2::operator/=(const Vector2 v) {
        *this = *this / v;
        return *this;
    }

    Vector2 Vector2::operator+(const float f) const {
        return {x + f, y + f};
    }

    Vector2 Vector2::operator-(const float f) const {
        return {x - f, y - f};
    }

    Vector2 Vector2::operator*(const float f) const {
        return {x * f, y * f};
    }

    Vector2 Vector2::operator/(const float f) const {
        if (f == 0) {
            return ZERO;
        }
        return {this->x / f, this->y / f};
    }

    Vector2 &Vector2::operator+=(const float f) {
        *this = *this + f;
        return *this;
    }

    Vector2 &Vector2::operator-=(const float f) {
        *this = *this - f;
        return *this;
    }

    Vector2 &Vector2::operator*=(const float f) {
        *this = *this * f;
        return *this;
    }

    Vector2 &Vector2::operator/=(const float f) {
        *this = *this / f;
        return *this;
    }

    std::string Vector2::to_string() const {
        return "{ x: " + std::to_string(x) + ", y: " + std::to_string(y) + " }";
    }

    Vector2 Vector2::clamp(const Vector2 min, const Vector2 max) const {
        return clamp_x(min.x, max.x).clamp_y(min.y, max.y);
    }

    Vector2 Vector2::clamp(const float min, const float max) const {
        return clamp_x(min, max).clamp_y(min, max);
    }

    Vector2 Vector2::clamp_x(const float min, const float max) const {
        if (x < min) {
            return {min, y};
        }
        return x > max ? Vector2(max, y) : *this;
    }

    Vector2 Vector2::clamp_y(const float min, const float max) const {
        if (y < min) {
            return {x, min};
        }
        return y > max ? Vector2(x, max) : *this;
    }

    float Vector2::distance_to(const Vector2 v) const {
        const auto d = v - *this;
        return sqrt(d.x * d.x + d.y * d.y);
    }

    float Vector2::dot(const Vector2 v) const {
        return x * v.x + y * v.y;
    }

    float Vector2::cross(const Vector2 v) const {
        return x * v.x - y * v.y;
    }

    Vector2 Vector2::rotate(const float degrees, const Vector2 v) const {
        const auto rad = degrees * (PI / 180);
        const auto cos = cos(rad);
        const auto sin = sin(rad);
        const auto translated = *this - v;
        const auto rotatedX = translated.x * cos - translated.y * sin;
        const auto rotatedY = translated.x * sin + translated.y * cos;
        return {rotatedX + v.x, rotatedY + v.y};
    }

    float Vector2::length() const {
        return sqrt(x * x + y * y);
    }

    float Vector2::angle_between(const Vector2 v) const {
        const auto lengths = length() * v.length();
        if (lengths == 0) {
            return 0;
        }
        return acos(dot(v) / lengths);
    }

    Vector2 Vector2::reflect(const Vector2 v) const {
        const auto dot = dot(v);
        return {x - 2 * dot * v.x, y - 2 * dot * v.y};
    }

    Vector2 Vector2::lerp(const Vector2 end, const float t) const {
        const auto clamped_t = std::max(0.f, std::min(1.f, t));
        return {x + (end.x - x) * clamped_t, y + (end.y - y) * clamped_t};
    }

    Vector2 Vector2::slerp(const Vector2 end, const float t) const {
        const auto angle = angle_between(end);
        return *this * cos(angle * t) + end * sin(angle * t);
    }

    Vector2 Vector2::round() const {
        return {std::round(x), std::round(y)};
    }

    Vector2 Vector2::abs() const {
        return {std::abs(x), std::abs(y)};
    }

    Vector2 Vector2::normalize() const {
        return *this / length();
    }

    float Vector2::modifier_x() const {
        if (x == 0) {
            return 0;
        }
        return x > 0 ? 1 : -1;
    }

    float Vector2::modifier_y() const {
        if (y == 0) {
            return 0;
        }
        return y > 0 ? 1 : -1;
    }

    Vector2 Vector2::modifiers() const {
        return {modifier_x(), modifier_y()};
    }
}
