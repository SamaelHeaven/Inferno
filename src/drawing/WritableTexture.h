#pragma once

#include "../inferno.h"
#include "./Texture.h"

namespace inferno {
    class WritableTexture final : public Texture {
    public:
        WritableTexture(int32_t width, int32_t height);

    private:
        internal::RenderTexture2D render_texture_{};

        friend class Texture;

        friend class Renderer;

        friend class Graphics;
    };
}
