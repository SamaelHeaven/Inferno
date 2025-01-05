#pragma once

#include "../inferno.h"

#include "../drawing/Color.h"
#include "../math/Vector2.h"

namespace inferno {
    class Renderer final {
    public:
        static void clear_background(Color color);

        static void draw_rectangle(const Vector2 &position, const Vector2 &size, const Color &color);

    private:
        static Renderer *instance_;

        internal::RenderTexture2D screen_{};

        Renderer();

        ~Renderer();

        static void update_();

        static void destroy_();

        static Renderer *get_();

        friend class Game;
    };
}
