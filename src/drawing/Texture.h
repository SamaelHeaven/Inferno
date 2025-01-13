#pragma once

#include "../core/Cleaner.h"
#include "../inferno.h"
#include "../math/Vector2.h"

namespace inferno {
    class WritableTexture;

    class Texture final {
    public:
        explicit Texture(const char *path);

        explicit Texture(const std::string &path);

        bool operator==(const Texture &other) const;

        [[nodiscard]] int32_t get_width() const;

        [[nodiscard]] int32_t get_height() const;

        [[nodiscard]] Vector2 get_size() const;

    private:
        explicit Texture(const internal::Texture2D &texture, bool unload = true);

        internal::Texture2D texture_;

        std::shared_ptr<Cleaner> cleaner_;

        friend class WritableTexture;
    };
}
