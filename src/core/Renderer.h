#pragma once

#include "../inferno.h"

#include "../drawing/Graphics.h"

namespace inferno {
    class Renderer final {
    public:
        static Graphics &get_graphics();

    private:
        static Renderer *instance_;

        WritableTexture screen_;

        Graphics graphics_;

        Renderer();

        ~Renderer();

        static void update_();

        static void destroy_();

        static Renderer *get_();

        friend class Game;

        friend class Graphics;
    };
}
