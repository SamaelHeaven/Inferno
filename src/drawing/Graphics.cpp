#include "Graphics.h"

#include "../core/Renderer.h"

namespace inferno {
    Graphics::Graphics(WritableTexture buffer) : buffer_(std::move(buffer)) {
        const auto renderer = Renderer::get_();
        const bool is_renderer = renderer->screen_ == buffer_;
        begin_draw_ = [&] {
            if (!is_renderer) {
                internal::EndTextureMode();
                BeginTextureMode(buffer_.render_texture_);
            }
        };
        end_draw_ = [&] {
            if (!is_renderer) {
                internal::EndTextureMode();
                BeginTextureMode(renderer->screen_.render_texture_);
            }
        };
    }

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

}
