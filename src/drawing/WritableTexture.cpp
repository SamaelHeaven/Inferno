#include "WritableTexture.h"

namespace inferno {
    WritableTexture::WritableTexture(const int32_t width, const int32_t height)
        : Texture(
              [&] {
                  render_texture_ = internal::LoadRenderTexture(width, height);
                  return render_texture_.texture;
              }(),
              false) {
        destroy_callback = [&] {
            destroy_callback();
            UnloadRenderTexture(render_texture_);
        };
    }
}
