#pragma once

#include <algorithm>
#include <boost/signals2/signal.hpp>
#include <box2d/box2d.h>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <entt/entity/registry.hpp>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#define MAGIC_ENUM_RANGE_MIN (-2048)
#define MAGIC_ENUM_RANGE_MAX 2048

#include <magic_enum/magic_enum_all.hpp>

namespace inferno::internal {
#include <raylib.h>
}

#define main inferno_main

#undef LIGHTGRAY
#undef GRAY
#undef DARKGRAY
#undef YELLOW
#undef GOLD
#undef ORANGE
#undef PINK
#undef RED
#undef MAROON
#undef GREEN
#undef LIME
#undef DARKGREEN
#undef SKYBLUE
#undef BLUE
#undef DARKBLUE
#undef PURPLE
#undef VIOLET
#undef DARKPURPLE
#undef BEIGE
#undef BROWN
#undef DARKBROWN
#undef WHITE
#undef BLACK
#undef BLANK
#undef MAGENTA
#undef RAYWHITE
