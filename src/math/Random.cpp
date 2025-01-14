#include "Random.h"

static std::random_device rd;

namespace inferno {
    Random::Random(const std::optional<uint32_t> seed) : seed(seed.value_or(rd())) { // NOLINT(*-msc51-cpp)
        engine_ = std::mt19937(this->seed);
    }

    int8_t Random::int8(const int8_t low, const int8_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    int16_t Random::int16(const int16_t low, const int16_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    int32_t Random::int32(const int32_t low, const int32_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    int64_t Random::int64(const int64_t low, const int64_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    uint8_t Random::uint8(const uint8_t low, const uint8_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    uint16_t Random::uint16(const uint16_t low, const uint16_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    uint32_t Random::uint32(const uint32_t low, const uint32_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    uint64_t Random::uint64(const uint64_t low, const uint64_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine_);
    }

    float Random::float32(const float low, const float high) {
        std::uniform_real_distribution dist(low, high);
        return dist(engine_);
    }

    double Random::float64(const double low, const double high) {
        std::uniform_real_distribution dist(low, high);
        return dist(engine_);
    }

    bool Random::boolean() {
        std::uniform_int_distribution dist(0, 1);
        return dist(engine_);
    }
}
