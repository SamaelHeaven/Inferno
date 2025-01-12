#include "Texture.h"

#include "./WritableTexture.h"

namespace inferno {
    std::unordered_map<uint32_t, uint32_t> Texture::textures_;

    Texture::Texture(const char *path) : Texture(internal::LoadTexture(path)) {}

    Texture::Texture(const std::string &path) : Texture(path.c_str()) {}

    Texture::Texture(const WritableTexture &texture) : Texture(texture.render_texture_.texture, true) {}

    Texture::~Texture() {
        if (const auto found_texture = textures_.find(texture_.id); found_texture != textures_.end()) {
            if (--found_texture->second == 0) {
                textures_.erase(texture_.id);
                if (is_writtable_) {
                    UnloadRenderTexture(dynamic_cast<WritableTexture *>(this)->render_texture_);
                } else {
                    UnloadTexture(texture_);
                }
            }
        }
    }

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
        : texture_(texture), is_writtable_(is_writtable) {
        if (const auto found_texture = textures_.find(texture_.id); found_texture == textures_.end()) {
            textures_[texture_.id] = 1;
        } else {
            found_texture->second++;
        }
    }

    Vector2 Texture::get_size() const {
        return {get_width(), get_height()};
    }
}
