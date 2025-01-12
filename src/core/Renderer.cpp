#include "Renderer.h"

#include "./Game.h"

namespace inferno {
    Graphics Renderer::graphics() {
        return get_()->graphics_;
    }

    void Renderer::update_() {
        const auto renderer = get_();
        const auto screen_width = static_cast<float>(Game::get_screen_width());
        const auto screen_height = static_cast<float>(Game::get_screen_height());
        const auto width = static_cast<float>(Game::get_width());
        const auto height = static_cast<float>(Game::get_height());
        const auto scale = std::min(screen_width / width, screen_height / height);
        const auto screen = renderer->screen_;
        const auto source = (internal::Rectangle){0.0f, 0.0f, width, -height};
        const auto dest = (internal::Rectangle){(screen_width - width * scale) * 0.5f,
            (screen_height - height * scale) * 0.5f, width * scale, height * scale};
        constexpr auto position = (internal::Vector2){0, 0};
        internal::EndTextureMode();
        internal::BeginDrawing();
        ClearBackground(internal::Color(0, 0, 0, 255));
        DrawTexturePro(
            screen.render_texture_.texture, source, dest, position, 0.0f, internal::Color(255, 255, 255, 255));
        internal::EndDrawing();
        BeginTextureMode(renderer->screen_.render_texture_);
    }

    void Renderer::destroy_() {
        delete get_();
    }

    Renderer *Renderer::instance_ = nullptr;

    Renderer::Renderer()
        : screen_(WritableTexture(Game::get_width(), Game::get_height())), graphics_(Graphics(screen_)) {
        Game::throw_if_uninitialized();
        BeginTextureMode(screen_.render_texture_);
    }

    Renderer::~Renderer() {
        instance_ = nullptr;
    }

    Renderer *Renderer::get_() {
        return instance_ = instance_ == nullptr ? new Renderer() : instance_;
    }
}
