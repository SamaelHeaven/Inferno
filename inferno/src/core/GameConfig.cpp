#include "./GameConfig.h"

namespace inferno {
    GameConfig::GameConfig() = default;

    GameConfig::GameConfig(const GameConfig &config) {
        title = config.title;
        icon = config.icon;
        width = config.width;
        height = config.height;
        screen_width = config.screen_width;
        screen_height = config.screen_height;
        fps_target = config.fps_target;
        fullscreen = config.fullscreen;
        decorated = config.decorated;
        vsync = config.vsync;
        resizable = config.resizable;
        debug = config.debug;
    }
}
