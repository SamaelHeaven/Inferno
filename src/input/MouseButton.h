#pragma once

#include "../inferno.h"

namespace inferno {
    enum class MouseButton {
        LEFT = internal::MouseButton::MOUSE_BUTTON_LEFT,
        RIGHT = internal::MouseButton::MOUSE_BUTTON_RIGHT,
        MIDDLE = internal::MouseButton::MOUSE_BUTTON_MIDDLE,
        SIDE = internal::MouseButton::MOUSE_BUTTON_SIDE,
        EXTRA = internal::MouseButton::MOUSE_BUTTON_EXTRA,
        FORWARD = internal::MouseButton::MOUSE_BUTTON_FORWARD,
        BACK = internal::MouseButton::MOUSE_BUTTON_BACK,
    };
}
