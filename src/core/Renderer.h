#pragma once

#include "../inferno.h"

#include "../drawing/Color.h"

namespace inferno {
    class Renderer final {
        public:
        static void clear_background(Color color);

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
