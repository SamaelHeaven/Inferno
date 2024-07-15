#include "Renderer.h"

#include "Game.h"
#include "../drawing/Color.h"

namespace inferno {
    void Renderer::clear_background(const Color &color) {
        const auto renderer = _get_instance();
        BeginTextureMode(renderer->_screen);
        ClearBackground(color._color);
        internal::EndTextureMode();
    }

    void Renderer::_update() {
        const auto renderer = _get_instance();
        const auto screen_width = static_cast<float>(Game::get_screen_width());
        const auto screen_height = static_cast<float>(Game::get_screen_height());
        const auto width = static_cast<float>(Game::get_width());
        const auto height = static_cast<float>(Game::get_height());
        const auto scale = std::min(screen_width / width, screen_height / height);
        const auto screen = renderer->_screen;
        const auto source = (internal::Rectangle){0.0f, 0.0f, width, -height};
        const auto dest = (internal::Rectangle){
            (screen_width - width * scale) * 0.5f, (screen_height - height * scale) * 0.5f, width * scale,
            height * scale
        };
        constexpr auto position = (internal::Vector2){0, 0};
        internal::BeginDrawing();
        ClearBackground(Color::BLACK._color);
        DrawTexturePro(screen.texture, source, dest, position, 0.0f, Color::WHITE._color);
        internal::EndDrawing();
    }

    void Renderer::_destroy() {
        delete _get_instance();
    }

    Renderer *Renderer::_instance = nullptr;

    Renderer::Renderer() {
        Game::throw_if_uninitialized();
        _screen = internal::LoadRenderTexture(Game::get_width(), Game::get_height());
        SetTextureFilter(_screen.texture, internal::TEXTURE_FILTER_BILINEAR);
    }

    Renderer::~Renderer() {
        UnloadRenderTexture(_screen);
    }

    Renderer *Renderer::_get_instance() {
        return _instance = _instance == nullptr ? new Renderer() : _instance;
    }
}
