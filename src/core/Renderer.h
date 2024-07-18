#pragma once

#include "../inferno.h"

#include "../drawing/Color.h"

namespace inferno {
    class Renderer final {
    public:
        static void clear_background(Color color);

    private:
        internal::RenderTexture2D _screen{};

        Renderer();

        ~Renderer();

        static void _update();

        static void _destroy();

        static Renderer *_get_instance();

        friend class Game;
    };
}
