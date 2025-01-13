#include "WritableTexture.h"

namespace inferno {
    WritableTexture::WritableTexture(const int32_t width, const int32_t height)
        : render_texture_(internal::LoadRenderTexture(width, height)), cleaner_(std::make_shared<Cleaner>([&] {
              UnloadRenderTexture(render_texture_);
          })) {}

    Texture WritableTexture::get_texture() const {
        return Texture(render_texture_.texture, false);
    }
}
