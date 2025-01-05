#include "coordinates.h"

#include "../core/Game.h"

namespace inferno::coordinates {
    Vector2 screen_to_local(Vector2 coordinates) {
        const auto size = Game::get_size();
        const auto screen_size = Game::get_screen_size();
        const auto scale = std::min(screen_size.x / size.x, screen_size.y / size.y);
        coordinates -= (screen_size - size * scale) * 0.5;
        coordinates /= scale;
        return coordinates;
    }

    Vector2 local_to_screen(Vector2 coordinates) {
        const auto size = Game::get_size();
        const auto screen_size = Game::get_screen_size();
        const auto scale = std::min(screen_size.x / size.x, screen_size.y / size.y);
        coordinates *= scale;
        coordinates += (screen_size - size * scale) * 0.5;
        return coordinates;
    }
}
