#pragma once

#include "../inferno.h"

#include "../math/Vector2.h"
#include "./GameConfig.h"
#include "./Scene.h"
#include "./file.h"

namespace inferno {
    class Game final {
    public:
        template <typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Scene, T>> * = nullptr,
                  std::enable_if_t<std::is_constructible_v<T, Args...>> * = nullptr>
        static void launch(const GameConfig &config, Args... args) {
            if (intance_ != nullptr) {
                throw std::runtime_error("Game as already been launched");
            }
            const auto _ = std::unique_ptr<Game>(get_());
            init_<T>(GameConfig(config), args...);
            run_();
        }

        static void throw_if_uninitialized();

        static std::shared_ptr<Scene> get_scene();

        static void set_scene(const std::shared_ptr<Scene> &scene);

        template <typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Scene, T>> * = nullptr,
                  std::enable_if_t<std::is_constructible_v<T, Args...>> * = nullptr>
        static void set_scene(Args... args) {
            set_scene(std::make_shared<T>(args...));
        }

        static int32_t get_screen_width();

        static void set_screen_width(int32_t width);

        static int32_t get_screen_height();

        static void set_screen_height(int32_t height);

        static Vector2 get_screen_size();

        static void set_screen_size(Vector2 size);

        static int32_t get_width();

        static int32_t get_height();

        static Vector2 get_size();

        static std::string get_title();

        static void set_title(const std::string &title);

        static bool is_fullscreen();

        static void set_fullscreen(bool fullscreen);

        static void toggle_fullscreen();

        static int32_t get_fps_target();

        static void set_fps_target(int32_t fps_target);

        static bool is_focused();

        ~Game();

    private:
        static Game *intance_;

        GameConfig config_;

        std::shared_ptr<Scene> scene_;

        Vector2 previous_screen_size_;

        bool reset_size_;

        Game();

        static Game *get_();

        template <typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Scene, T>> * = nullptr,
                  std::enable_if_t<std::is_constructible_v<T, Args...>> * = nullptr>
        static void init_(const GameConfig &config, Args... args) {
            const auto game = get_();
            const auto screen_width = config.screen_width >= 0 ? config.screen_width : config.width;
            const auto screen_height = config.screen_height >= 0 ? config.screen_height : config.height;
            game->config_ = config;
            game->scene_ = std::make_shared<T>(args...);
            game->previous_screen_size_ = {config.width, config.height};
            SetTraceLogLevel(config.debug ? internal::LOG_ALL : internal::LOG_NONE);
            internal::SetConfigFlags(get_config_flags_(config));
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

        static uint32_t get_config_flags_(const GameConfig &config);

        static void run_();
    };
}
