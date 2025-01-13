#include "Graphics.h"

#include <utility>

#include "../core/Renderer.h"

namespace inferno {
    Graphics::Graphics(const WritableTexture &buffer) : Graphics(buffer, false) {}

    Graphics::Graphics(const WritableTexture &buffer, const bool is_renderer)
        : buffer_(buffer), is_renderer_(is_renderer) {}

    void Graphics::clear_background(const Color color) const {
        begin_draw_();
        ClearBackground(internal::Color(color.red, color.green, color.blue, color.alpha));
        end_draw_();
    }

    void Graphics::draw_rectangle(const Vector2 position, const Vector2 size, const Color color) const {
        begin_draw_();
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x),
            static_cast<int>(size.y), internal::Color(color.red, color.green, color.blue, color.alpha));
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
