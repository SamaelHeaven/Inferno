#include "./Game.h"

#include "./file.h"
#include "./Time.h"
#include "./Renderer.h"
#include "../input/Keyboard.h"
#include "../input/Mouse.h"

namespace inferno {
    void Game::launch(const GameConfig &config, const std::shared_ptr<Scene> &scene) {
        if (_instance != nullptr) {
            throw std::runtime_error("Game as already been launched");
        }
        const auto _ = std::unique_ptr<Game>(_get_instance());
        _init(GameConfig(config), scene);
        _run();
    }

    void Game::throw_if_uninitialized() {
        if (_instance == nullptr) {
            throw std::runtime_error("Game has not been launched yet");
        }
    }

    std::shared_ptr<Scene> Game::get_scene() {
        throw_if_uninitialized();
        return _get_instance()->_scene;
    }

    void Game::set_scene(const std::shared_ptr<Scene> &scene) {
        throw_if_uninitialized();
        _get_instance()->_scene = scene;
    }

    int32_t Game::get_screen_width() {
        throw_if_uninitialized();
        return internal::GetScreenWidth();
    }

    void Game::set_screen_width(const int32_t width) {
        throw_if_uninitialized();
        if (get_screen_width() == width) {
            return;
        }
        internal::SetWindowSize(width, get_screen_height());
    }

    int32_t Game::get_screen_height() {
        throw_if_uninitialized();
        return internal::GetScreenHeight();
    }

    void Game::set_screen_height(const int32_t height) {
        throw_if_uninitialized();
        if (get_screen_height() == height) {
            return;
        }
        internal::SetWindowSize(get_screen_width(), height);
    }

    Vector2 Game::get_screen_size() {
        throw_if_uninitialized();
        return {get_screen_width(), get_screen_height()};
    }

    void Game::set_screen_size(Vector2 size) {
        throw_if_uninitialized();
        size = size.round();
        if (get_screen_size() == size) {
            return;
        }
        internal::SetWindowSize(static_cast<int32_t>(size.x), static_cast<int32_t>(size.y));
    }

    int32_t Game::get_width() {
        throw_if_uninitialized();
        return _get_instance()->_config.width;
    }

    int32_t Game::get_height() {
        throw_if_uninitialized();
        return _get_instance()->_config.height;
    }

    Vector2 Game::get_size() {
        throw_if_uninitialized();
        return {get_width(), get_height()};
    }

    std::string Game::get_title() {
        throw_if_uninitialized();
        return _get_instance()->_config.title;
    }

    void Game::set_title(const std::string &title) {
        throw_if_uninitialized();
        if (get_title() == title) {
            return;
        }
        _get_instance()->_config.title = title;
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
#ifdef PLATFORM_DESKTOP
        internal::ToggleFullscreen();
#endif
    }

    int32_t Game::get_fps_target() {
        throw_if_uninitialized();
        return _get_instance()->_config.fps_target;
    }

    void Game::set_fps_target(const int32_t fps_target) {
        throw_if_uninitialized();
        if (get_fps_target() == fps_target) {
            return;
        }
        _get_instance()->_config.fps_target = fps_target;
        internal::SetTargetFPS(fps_target);
        Time::_restart();
    }

    bool Game::is_focused() {
        throw_if_uninitialized();
#ifdef PLATFORM_DESKTOP
        return internal::IsWindowFocused();
#else
        return true;
#endif
    }

    Game::~Game() {
        Time::_destroy();
        Keyboard::_destroy();
        Mouse::_destroy();
        Renderer::_destroy();
        internal::CloseWindow();
    }

    Game *Game::_instance = nullptr;

    Game::Game() = default;

    Game *Game::_get_instance() {
        return _instance = _instance == nullptr ? new Game() : _instance;
    }

    void Game::_init(const GameConfig &config, const std::shared_ptr<Scene> &scene) {
        const auto game = _get_instance();
        const auto screen_width = config.screen_width >= 0 ? config.screen_width : config.width;
        const auto screen_height = config.screen_height >= 0 ? config.screen_height : config.height;
        game->_config = config;
        game->_scene = scene;
        SetTraceLogLevel(config.debug ? internal::LOG_ALL : internal::LOG_NONE);
        internal::SetConfigFlags(_get_config_flags(config));
        internal::InitWindow(config.width, config.height, config.title.c_str());
        internal::SetTargetFPS(config.fps_target);
        SetExitKey(internal::KeyboardKey::KEY_NULL);
        internal::SetWindowSize(screen_width, screen_height);
        if (config.fullscreen) {
            toggle_fullscreen();
        }
#ifdef PLATFORM_DESKTOP
        if (file::is_file(config.icon)) {
            const auto icon = internal::LoadImage(file::format_path(config.icon).c_str());
            SetWindowIcon(icon);
            UnloadImage(icon);
        }
#endif
    }

    uint32_t Game::_get_config_flags(const GameConfig &config) {
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

    void Game::_run() {
        const auto game = _get_instance();
        auto scene = game->_scene;
        while (!internal::WindowShouldClose()) {
            Time::_update();
            Keyboard::_update();
            Mouse::_update();
            if (scene.get() != game->_scene.get()) {
                scene = game->_scene;
            }
            scene->_initialize();
            scene->_update();
            Renderer::_update();
        }
    }
}
