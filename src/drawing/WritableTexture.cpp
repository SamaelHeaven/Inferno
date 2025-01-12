#include "WritableTexture.h"

namespace inferno {
    WritableTexture::WritableTexture(const int32_t width, const int32_t height)
        : Texture((render_texture_ = internal::LoadRenderTexture(width, height)).texture, false) {
        const auto old_destroy_callback = destroy_callback;
        destroy_callback = [&] {
            old_destroy_callback();
            UnloadRenderTexture(render_texture_);
        };
    }
}
