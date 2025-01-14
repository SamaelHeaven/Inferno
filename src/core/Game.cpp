#include "Game.h"

#include "../input/Gamepad.h"
#include "../input/Keyboard.h"
#include "../input/Mouse.h"
#include "./Renderer.h"
#include "./Time.h"

namespace inferno {
    void Game::throw_if_initialized() {
        if (intance_ != nullptr) {
            throw std::runtime_error("Game has already been launched");
        }
    }

    void Game::throw_if_uninitialized() {
        if (intance_ == nullptr) {
            throw std::runtime_error("Game has not been launched yet");
        }
    }

    std::shared_ptr<Scene> Game::get_scene() {
        throw_if_uninitialized();
        return get_()->scene_;
    }

    void Game::set_scene(const std::shared_ptr<Scene> &scene) {
        throw_if_uninitialized();
        get_()->scene_ = scene;
    }

    int32_t Game::get_screen_width() {
        throw_if_uninitialized();
        return internal::GetScreenWidth();
    }

    void Game::set_screen_width(const int32_t width) {
        throw_if_uninitialized();
#ifdef PLATFORM_DESKTOP
        if (is_fullscreen() && width != get_width()) {
            return;
        }
        if (get_screen_width() == width) {
            return;
        }
        internal::SetWindowSize(width, get_screen_height());
#endif
    }

    int32_t Game::get_screen_height() {
        throw_if_uninitialized();
        return internal::GetScreenHeight();
    }

    void Game::set_screen_height(const int32_t height) {
        throw_if_uninitialized();
#ifdef PLATFORM_DESKTOP
        if (is_fullscreen() && height != get_height()) {
            return;
        }
        if (get_screen_height() == height) {
            return;
        }
        internal::SetWindowSize(get_screen_width(), height);
#endif
    }

    Vector2 Game::get_screen_size() {
        throw_if_uninitialized();
        return {get_screen_width(), get_screen_height()};
    }

    void Game::set_screen_size(Vector2 size) {
        throw_if_uninitialized();
#ifdef PLATFORM_DESKTOP
        size = size.round();
        if (is_fullscreen() && size != get_size()) {
            return;
        }
        if (get_screen_size() == size) {
            return;
        }
        internal::SetWindowSize(static_cast<int32_t>(size.x), static_cast<int32_t>(size.y));
#endif
    }

    int32_t Game::get_width() {
        throw_if_uninitialized();
        return get_()->config_.width;
    }

    int32_t Game::get_height() {
        throw_if_uninitialized();
        return get_()->config_.height;
    }

    Vector2 Game::get_size() {
        throw_if_uninitialized();
        return {get_width(), get_height()};
    }

    std::string Game::get_title() {
        throw_if_uninitialized();
        return get_()->config_.title;
    }

    Interpolation Game::get_default_interpolation() {
        throw_if_uninitialized();
        return get_()->config_.default_interpolation;
    }

    void Game::set_title(const std::string &title) {
        throw_if_uninitialized();
        if (get_title() == title) {
            return;
        }
        get_()->config_.title = title;
        internal::SetWindowTitle(title.c_str());
    }

    bool Game::is_fullscreen() {
        throw_if_uninitialized();
        return internal::IsWindowFullscreen();
    }

    void Game::set_fullscreen(const bool fullscreen) {
        throw_if_uninitialized();
        if (is_fullscreen() != fullscreen) {
            toggle_fullscreen();
        }
    }

    void Game::toggle_fullscreen() {
        throw_if_uninitialized();
        const auto game = get_();
        if (is_fullscreen()) {
            game->reset_size_ = true;
        } else {
            game->previous_screen_size_ = get_screen_size();
            set_screen_size(get_size());
        }
        internal::ToggleFullscreen();
    }

    int32_t Game::get_fps_target() {
        throw_if_uninitialized();
        return get_()->config_.fps_target;
    }

    void Game::set_fps_target(const int32_t fps_target) {
        throw_if_uninitialized();
        if (get_fps_target() == fps_target) {
            return;
        }
        get_()->config_.fps_target = fps_target;
        internal::SetTargetFPS(fps_target);
        Time::restart_();
    }

    bool Game::is_focused() {
        throw_if_uninitialized();
        return internal::IsWindowFocused();
    }

    Game::~Game() {
        Time::destroy_();
        Keyboard::destroy_();
        Mouse::destroy_();
        Gamepad::destroy_();
        Renderer::destroy_();
        internal::CloseWindow();
        intance_ = nullptr;
    }

    Game *Game::intance_ = nullptr;

    Game::Game() {
        reset_size_ = false;
    }

    Game *Game::get_() {
        return intance_ = intance_ == nullptr ? new Game() : intance_;
    }

    uint32_t Game::get_config_flags_(const GameConfig &config) {
        uint32_t flags = 0;
        if (config.resizable) {
            flags |= internal::FLAG_WINDOW_RESIZABLE;
        }
        if (!config.decorated) {
            flags |= internal::FLAG_WINDOW_UNDECORATED;
        }
        if (config.vsync) {
            flags |= internal::FLAG_VSYNC_HINT;
        }
        return flags;
    }

    void Game::run_() {
        const auto game = get_();
        auto scene = game->scene_;
        while (!internal::WindowShouldClose()) {
            Time::update_();
            Keyboard::update_();
            Mouse::update_();
            Gamepad::update_all_();
            if (game->reset_size_) {
                set_screen_size(game->previous_screen_size_);
                if (get_screen_size() == game->previous_screen_size_) {
                    game->reset_size_ = false;
                }
            }
            if (scene.get() != game->scene_.get()) {
                scene = game->scene_;
            }
            scene->initialize_();
            scene->update_();
            Renderer::update_();
        }
    }
}
