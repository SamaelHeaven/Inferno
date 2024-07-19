#pragma once

#include "../math/Vector2.h"

namespace inferno::coordinates {
    Vector2 screen_to_local(Vector2 coordinates);

    Vector2 local_to_screen(Vector2 coordinates);
}
