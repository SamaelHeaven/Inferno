#include "./random.h"

static std::random_device rd;
static std::mt19937 engine(rd());

namespace inferno::random {
    int8_t int8(const int8_t low, const int8_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    int16_t int16(const int16_t low, const int16_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    int32_t int32(const int32_t low, const int32_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    int64_t int64(const int64_t low, const int64_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    uint8_t uint8(const uint8_t low, const uint8_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    uint16_t uint16(const uint16_t low, const uint16_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    uint32_t uint32(const uint32_t low, const uint32_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    uint64_t uint64(const uint64_t low, const uint64_t high) {
        std::uniform_int_distribution dist(low, high);
        return dist(engine);
    }

    float float32(const float low, const float high) {
        std::uniform_real_distribution dist(low, high);
        return dist(engine);
    }

    double float64(const double low, const double high) {
        std::uniform_real_distribution dist(low, high);
        return dist(engine);
    }

    bool boolean() {
        std::uniform_int_distribution dist(0, 1);
        return dist(engine);
    }
}
