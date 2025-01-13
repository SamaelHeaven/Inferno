#include "Graphics.h"

#include "../core/Renderer.h"

#define INTERNAL_RECTANGLE(position, size)                                                                             \
    { .x = position.x, .y = position.y, .width = size.x, .height = size.y }

#define INTERNAL_COLOR(color) internal::Color(color.red, color.green, color.blue, color.alpha)

namespace inferno {
    Graphics::Graphics(const WritableTexture &buffer) : Graphics(buffer, false) {}

    Graphics::Graphics(WritableTexture buffer, const bool is_renderer)
        : buffer_(std::move(buffer)), is_renderer_(is_renderer) {}

    void Graphics::clear_background(const Color color) const {
        begin_draw_();
        ClearBackground(INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::fill_rectangle(const Vector2 position, const Vector2 size, const Color color) const {
        begin_draw_();
        DrawRectangleRec(INTERNAL_RECTANGLE(position, size), INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::stroke_rectangle(
        const Vector2 position, const Vector2 size, const Color color, const float stroke_width) const {
        begin_draw_();
        DrawRectangleLinesEx(INTERNAL_RECTANGLE(position, size), stroke_width, INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::begin_draw_() const {
        if (!is_renderer_) {
            internal::EndTextureMode();
            BeginTextureMode(buffer_.render_texture_);
        }
    }

    void Graphics::end_draw_() const {
        if (!is_renderer_) {
            internal::EndTextureMode();
            BeginTextureMode(Renderer::get_()->screen_.render_texture_);
        }
    }
}
