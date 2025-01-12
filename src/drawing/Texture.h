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
        explicit Texture(const internal::Texture2D &texture, bool is_writtable = true);

    private:
        class Cleaner {
        public:
            explicit Cleaner(const std::function<void()> &destroy);

            ~Cleaner();

        private:
            std::function<void()> destroy_;
        };

        internal::Texture2D texture_;

        bool is_writtable_;

        std::shared_ptr<Cleaner> cleaner_;
    };
}
