#pragma once

#include "../inferno.h"

namespace inferno {
    enum class Interpolation {
        NONE = internal::TextureFilter::TEXTURE_FILTER_POINT,
        BILINEAR = internal::TextureFilter::TEXTURE_FILTER_BILINEAR,
        TRILINEAR = internal::TextureFilter::TEXTURE_FILTER_TRILINEAR,
        ANISOTROPIC_4X = internal::TextureFilter::TEXTURE_FILTER_ANISOTROPIC_4X,
        ANISOTROPIC_8X = internal::TextureFilter::TEXTURE_FILTER_ANISOTROPIC_8X,
        ANISOTROPIC_16X = internal::TextureFilter::TEXTURE_FILTER_ANISOTROPIC_16X
    };
}
