#pragma once

#include "../inferno.h"

namespace inferno {
    enum class Cursor {
        DEFAULT = internal::MOUSE_CURSOR_DEFAULT,
        ARROW = internal::MOUSE_CURSOR_ARROW,
        IBEAM = internal::MOUSE_CURSOR_IBEAM,
        CROSSHAIR = internal::MOUSE_CURSOR_CROSSHAIR,
        POINTING_HAND = internal::MOUSE_CURSOR_POINTING_HAND,
        RESIZE_EW = internal::MOUSE_CURSOR_RESIZE_EW,
        RESIZE_NS = internal::MOUSE_CURSOR_RESIZE_NS,
        RESIZE_NWSE = internal::MOUSE_CURSOR_RESIZE_NWSE,
        RESIZE_NESW = internal::MOUSE_CURSOR_RESIZE_NESW,
        RESIZE_ALL = internal::MOUSE_CURSOR_RESIZE_ALL,
        NOT_ALLOWED = internal::MOUSE_CURSOR_NOT_ALLOWED,
        NONE,
    };
}
