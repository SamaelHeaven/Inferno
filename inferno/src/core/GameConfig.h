#pragma once

#include "../inferno.h"

namespace inferno {
    struct GameConfig final {
        std::string title{};
        std::string icon{};
        int32_t width = 800;
        int32_t height = 600;
        int32_t screen_width = -1;
        int32_t screen_height = -1;
        int32_t fps_target = 60;
        bool fullscreen = false;
        bool decorated = true;
        bool vsync = true;
        bool resizable = true;
        bool debug = false;

        GameConfig();

        GameConfig(const GameConfig &config);
    };
}
