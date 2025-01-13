#pragma once

#include "./Color.h"
#include "./WritableTexture.h"

namespace inferno {
    class Graphics {
    public:
        void clear_background(Color color) const;

        void fill_rectangle(Vector2 position, Vector2 size, Color color) const;

        void stroke_rectangle(Vector2 position, Vector2 size, Color color, float stroke_width) const;

        explicit Graphics(const WritableTexture &buffer);

    private:
        Graphics(WritableTexture buffer, bool is_renderer);

        WritableTexture buffer_;

        bool is_renderer_;

        void begin_draw_() const;

        void end_draw_() const;

        friend class Renderer;
    };
}
