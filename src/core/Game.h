#pragma once

#include "../inferno.h"

#include "./GameConfig.h"
#include "./Scene.h"

namespace inferno {
    class Game final {
    public:
        static void launch(const GameConfig &config, const std::shared_ptr<Scene> &scene);

        template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Scene, T> >* = nullptr,
            std::enable_if_t<std::is_constructible_v<T, Args...> >* = nullptr>
        static void launch(const GameConfig &config, Args... args) {
            launch(config, std::make_shared<T>(args...));
        }

        static void throw_if_uninitialized();

        static std::shared_ptr<Scene> get_scene();

        static void set_scene(const std::shared_ptr<Scene> &scene);

        template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Scene, T> >* = nullptr,
            std::enable_if_t<std::is_constructible_v<T, Args...> >* = nullptr>
        static void set_scene(Args... args) {
            set_scene(std::make_shared<T>(args...));
        }

        static int32_t get_screen_width();

        static void set_screen_width(int32_t width);

        static int32_t get_screen_height();

        static void set_screen_height(int32_t height);

        static int32_t get_width();

        static int32_t get_height();

        static bool is_focused();

        ~Game();

    private:
        static Game *_instance;

        GameConfig _config;

        std::shared_ptr<Scene> _scene;

        Game();

        static Game *_get_instance();

        static void _init(const GameConfig &config, const std::shared_ptr<Scene> &scene);

        static uint32_t _get_config_flags(const GameConfig &config);

        static void _run();
    };
}
