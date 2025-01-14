#pragma once

#include "./Color.h"
#include "./Rectangle.h"
#include "./WritableTexture.h"

namespace inferno {
    class Graphics {
    public:
        explicit Graphics(const WritableTexture &buffer);

        static Graphics &current();

        static void push_state();

        static void pop_state();

        static void translate(Vector2 translation);

        static void rotate(float angle);

        static void scale(Vector2 scale);

        void clear_background(Color color) const;

        void fill_rectangle(Vector2 position, Vector2 size, Color color) const;

        void stroke_rectangle(Vector2 position, Vector2 size, Color color, float stroke_width) const;

        void draw_rectangle(const Rectangle &rectangle) const;

        void fill_rounded_rectangle(Vector2 position, Vector2 size, Color color, float radius) const;

        void stroke_rounded_rectangle(
            Vector2 position, Vector2 size, Color color, float radius, float stroke_width) const;

    private:
        Graphics(WritableTexture buffer, bool is_renderer);

        WritableTexture buffer_;

        bool is_renderer_;

        void begin_draw_() const;

        void end_draw_() const;

        friend class Renderer;
    };
}
