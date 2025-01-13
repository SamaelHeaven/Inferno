#include "WritableTexture.h"

namespace inferno {
    WritableTexture::WritableTexture(const int32_t width, const int32_t height)
        : render_texture_(internal::LoadRenderTexture(width, height)), cleaner_(std::make_shared<Cleaner>([&] {
              UnloadRenderTexture(render_texture_);
          })) {}

    WritableTexture::WritableTexture(const WritableTexture &other)
        : render_texture_({.id = other.render_texture_.id,
              .texture = {.id = other.render_texture_.texture.id,
                  .width = other.render_texture_.texture.width,
                  .height = other.render_texture_.texture.height,
                  .mipmaps = other.render_texture_.texture.mipmaps,
                  .format = other.render_texture_.texture.format},
              .depth = {.id = other.render_texture_.depth.id,
                  .width = other.render_texture_.depth.width,
                  .height = other.render_texture_.depth.height,
                  .mipmaps = other.render_texture_.depth.mipmaps,
                  .format = other.render_texture_.depth.format}}),
          cleaner_(other.cleaner_) {}

    Texture WritableTexture::get_texture() const {
        return Texture(render_texture_.texture, false);
    }
}
