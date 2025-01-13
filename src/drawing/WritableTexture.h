#pragma once

#include "../inferno.h"
#include "./Texture.h"

namespace inferno {
    class WritableTexture final {
    public:
        WritableTexture(int32_t width, int32_t height);

        WritableTexture(const WritableTexture &other);

        [[nodiscard]] Texture get_texture() const;

    private:
        internal::RenderTexture2D render_texture_;

        std::shared_ptr<Cleaner> cleaner_;

        friend class Renderer;

        friend class Graphics;
    };
}
