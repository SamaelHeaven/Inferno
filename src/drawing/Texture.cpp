#include "Texture.h"

#include "./WritableTexture.h"

namespace inferno {
    Texture::Texture(const char *path) : Texture(internal::LoadTexture(path)) {}

    Texture::Texture(const std::string &path) : Texture(path.c_str()) {}

    Texture::Texture(const WritableTexture &texture) : Texture(texture.render_texture_.texture, true) {}

    Texture::~Texture() = default;

    bool Texture::operator==(const Texture &other) const {
        return texture_.id == other.texture_.id;
    }

    int32_t Texture::get_width() const {
        return texture_.width;
    }

    int32_t Texture::get_height() const {
        return texture_.height;
    }

    Texture::Texture(const internal::Texture2D &texture, const bool is_writtable)
        : texture_(texture), is_writtable_(is_writtable), cleaner_(std::make_shared<Cleaner>([&] {
              if (is_writtable_) {
                  UnloadRenderTexture(dynamic_cast<WritableTexture *>(this)->render_texture_);
              } else {
                  UnloadTexture(texture_);
              }
          })) {}

    Vector2 Texture::get_size() const {
        return {get_width(), get_height()};
    }

    Texture::Cleaner::Cleaner(const std::function<void()> &destroy) {
        destroy_ = destroy;
    }

    Texture::Cleaner::~Cleaner() {
        destroy_();
    }

}
