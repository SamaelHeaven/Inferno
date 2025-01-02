#include "./Renderer.h"

#include "../drawing/Color.h"
#include "./Game.h"

namespace inferno {
    void Renderer::clear_background(const Color color) {
        const auto renderer = get_();
        BeginTextureMode(renderer->screen_);
        ClearBackground(internal::Color(color.red, color.green, color.blue, color.alpha));
        internal::EndTextureMode();
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
        internal::BeginDrawing();
        ClearBackground(internal::Color(0, 0, 0, 255));
        DrawTexturePro(screen.texture, source, dest, position, 0.0f, internal::Color(255, 255, 255, 255));
        internal::EndDrawing();
    }

    void Renderer::destroy_() {
        delete get_();
    }

    Renderer *Renderer::instance_ = nullptr;

    Renderer::Renderer() {
        Game::throw_if_uninitialized();
        screen_ = internal::LoadRenderTexture(Game::get_width(), Game::get_height());
        SetTextureFilter(screen_.texture, internal::TEXTURE_FILTER_BILINEAR);
    }

    Renderer::~Renderer() {
        UnloadRenderTexture(screen_);
        instance_ = nullptr;
    }

    Renderer *Renderer::get_() {
        return instance_ = instance_ == nullptr ? new Renderer() : instance_;
    }
}
