#pragma once

#include "../inferno.h"

namespace inferno {
    enum class Interpolation {
        NONE = internal::TextureFilter::TEXTURE_FILTER_POINT,
        BILINEAR = internal::TextureFilter::TEXTURE_FILTER_BILINEAR,
        TRILINEAR = internal::TextureFilter::TEXTURE_FILTER_TRILINEAR
    };
}
