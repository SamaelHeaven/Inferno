#pragma once

#include "../inferno.h"

namespace inferno {
    class Random {
    public:
        explicit Random(std::optional<uint32_t> seed = std::nullopt);

        const uint32_t seed;

        [[nodiscard]] int8_t int8(int8_t low, int8_t high) const;

        [[nodiscard]] int16_t int16(int16_t low, int16_t high) const;

        [[nodiscard]] int32_t int32(int32_t low, int32_t high) const;

        [[nodiscard]] int64_t int64(int64_t low, int64_t high) const;

        [[nodiscard]] uint8_t uint8(uint8_t low, uint8_t high) const;

        [[nodiscard]] uint16_t uint16(uint16_t low, uint16_t high) const;

        [[nodiscard]] uint32_t uint32(uint32_t low, uint32_t high) const;

        [[nodiscard]] uint64_t uint64(uint64_t low, uint64_t high) const;

        [[nodiscard]] float float32(float low, float high) const;

        [[nodiscard]] double float64(double low, double high) const;

        [[nodiscard]] bool boolean() const;

    private:
        mutable std::mt19937 engine_;
    };

    extern const Random random;
}
