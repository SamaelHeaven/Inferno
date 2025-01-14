#include "Graphics.h"

#include "../core/Renderer.h"

#define INTERNAL_RECTANGLE(position, size)                                                                             \
    { .x = position.x, .y = position.y, .width = size.x, .height = size.y }

#define INTERNAL_COLOR(color) internal::Color(color.red, color.green, color.blue, color.alpha)

namespace inferno {
    Graphics::Graphics(const WritableTexture &buffer) : Graphics(buffer, false) {}

    Graphics::Graphics(WritableTexture buffer, const bool is_renderer)
        : buffer_(std::move(buffer)), is_renderer_(is_renderer) {}

    void Graphics::system(ECS &ecs) {
        const auto &graphics = current();

        ecs.on_ordered_update([&](const Entity entity) {
            if (const auto rectangle = ecs.get<Rectangle>(entity)) {
                graphics.draw_rectangle(*rectangle);
            }
        });
    }

    Graphics &Graphics::current() {
        return Renderer::get_graphics();
    }

    void Graphics::push_state() {
        internal::rlPushMatrix();
    }

    void Graphics::pop_state() {
        internal::rlPopMatrix();
    }

    void Graphics::translate(const Vector2 translation) {
        internal::rlTranslatef(translation.x, translation.y, 0.0f);
    }

    void Graphics::rotate(const float angle) {
        internal::rlRotatef(angle, 0, 0, 1);
    }

    void Graphics::scale(const Vector2 scale) {
        internal::rlScalef(scale.x, scale.y, 1.0f);
    }

    void Graphics::clear_background(const Color color) const {
        if (color == Color::TRANSPARENT) {
            return;
        }
        begin_draw_();
        ClearBackground(INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::fill_rectangle(const Vector2 position, const Vector2 size, const Color color) const {
        if (color == Color::TRANSPARENT) {
            return;
        }
        begin_draw_();
        DrawRectangleRec(INTERNAL_RECTANGLE(position, size), INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::stroke_rectangle(
        const Vector2 position, const Vector2 size, const Color color, const float stroke_width) const {
        if (color == Color::TRANSPARENT || stroke_width <= 0) {
            return;
        }
        begin_draw_();
        DrawRectangleLinesEx(INTERNAL_RECTANGLE(position, size), stroke_width, INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::draw_rectangle(const Rectangle &rectangle) const {
        const auto position = rectangle.get_position();
        const auto scale = rectangle.get_scale();
        const auto origin = rectangle.get_origin();
        const auto pivot_point = rectangle.get_pivot_point();
        const auto rotation = rectangle.get_rotation();
        const auto fill = rectangle.get_fill();
        const auto stroke = rectangle.get_stroke();
        const auto stroke_width = rectangle.get_stroke_width();
        const auto radius = rectangle.get_radius();
        const auto half_scale = scale * 0.5;
        const auto position_offset = -(half_scale - scale * (origin.clamp(-1, 1) * 0.5));
        const auto rotation_offset = position - position_offset - (half_scale - scale * (pivot_point * 0.5));
        push_state();
        translate(rotation_offset);
        rotate(rotation);
        translate(-rotation_offset + position_offset);
        if (radius <= 0) {
            fill_rectangle(position, scale, fill);
            stroke_rectangle(position, scale, stroke, stroke_width);
        } else {
            fill_rounded_rectangle(position, scale, fill, radius);
            stroke_rounded_rectangle(position, scale, stroke, radius, stroke_width);
        }
        pop_state();
    }

    void Graphics::fill_rounded_rectangle(
        const Vector2 position, const Vector2 size, const Color color, const float radius) const {
        if (color == Color::TRANSPARENT) {
            return;
        }
        begin_draw_();
        DrawRectangleRounded(INTERNAL_RECTANGLE(position, size), radius, 0, INTERNAL_COLOR(color));
        end_draw_();
    }

    void Graphics::stroke_rounded_rectangle(const Vector2 position, const Vector2 size, const Color color,
        const float radius, const float stroke_width) const {
        if (color == Color::TRANSPARENT || stroke_width <= 0) {
            return;
        }
        begin_draw_();
        DrawRectangleRoundedLinesEx(INTERNAL_RECTANGLE(position, size), radius, 0, stroke_width, INTERNAL_COLOR(color));
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
