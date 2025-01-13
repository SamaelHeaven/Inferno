#include "Texture.h"

namespace inferno {
    Texture::Texture(const char *path) : Texture(internal::LoadTexture(path)) {}

    Texture::Texture(const std::string &path) : Texture(path.c_str()) {}

    Texture::Texture(const Texture &other)
        : texture_({.id = other.texture_.id,
              .width = other.texture_.width,
              .height = other.texture_.height,
              .mipmaps = other.texture_.mipmaps,
              .format = other.texture_.format}),
          cleaner_(other.cleaner_) {}

    bool Texture::operator==(const Texture &other) const {
        return texture_.id == other.texture_.id;
    }

    int32_t Texture::get_width() const {
        return texture_.width;
    }

    int32_t Texture::get_height() const {
        return texture_.height;
    }

    Texture::Texture(const internal::Texture2D &texture, const bool unload)
        : texture_(texture), cleaner_(std::make_shared<Cleaner>([&] {
              if (unload) {
                  UnloadTexture(texture_);
              }
          })) {}

    Vector2 Texture::get_size() const {
        return {get_width(), get_height()};
    }
}
