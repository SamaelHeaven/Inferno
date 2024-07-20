#pragma once

#include "../inferno.h"

namespace inferno::random {
    int8_t int8(int8_t low, int8_t high);
    int16_t int16(int16_t low, int16_t high);
    int32_t int32(int32_t low, int32_t high);
    int64_t int64(int64_t low, int64_t high);
    uint8_t uint8(uint8_t low, uint8_t high);
    uint16_t uint16(uint16_t low, uint16_t high);
    uint32_t uint32(uint32_t low, uint32_t high);
    uint64_t uint64(uint64_t low, uint64_t high);
    float float32(float low, float high);
    double float64(double low, double high);
    bool boolean();
}
