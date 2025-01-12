#pragma once

#include "../inferno.h"
#include "../math/Vector2.h"

namespace inferno {
    class WritableTexture;

    class Texture {
    public:
        explicit Texture(const char *path);

        explicit Texture(const std::string &path);

        Texture(const WritableTexture &texture); // NOLINT(*-explicit-constructor)

        virtual ~Texture();

        bool operator==(const Texture &other) const;

        [[nodiscard]] int32_t get_width() const;

        [[nodiscard]] int32_t get_height() const;

        [[nodiscard]] Vector2 get_size() const;

    protected:
        std::function<void()> destroy_callback;

        explicit Texture(const internal::Texture2D &texture, bool unload = true);

    private:
        static std::unordered_map<uint32_t, uint32_t> textures_;

        internal::Texture2D texture_;
    };
}
