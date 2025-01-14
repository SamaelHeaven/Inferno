#pragma once

#include "../drawing/Graphics.h"
#include "../drawing/Interpolation.h"

namespace inferno {
    class Renderer final {
    public:
        static Graphics &get_graphics();

        static Interpolation get_interpolation();

        static void set_interpolation(Interpolation interpolation);

    private:
        static Renderer *instance_;

        WritableTexture screen_;

        Graphics graphics_;

        Interpolation interpolation_;

        Renderer();

        ~Renderer();

        static void update_();

        static void destroy_();

        static Renderer *get_();

        friend class Game;

        friend class Graphics;
    };
}
