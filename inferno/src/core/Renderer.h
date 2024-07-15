#pragma once

#include "../inferno.h"

namespace inferno {
    class Renderer final {
    public:
        static void clear_background(const class Color &color);

    private:
        static Renderer *_instance;

        internal::RenderTexture2D _screen{};

        Renderer();

        ~Renderer();

        static void _update();

        static void _destroy();

        static Renderer *_get_instance();

        friend class Game;
    };
}
