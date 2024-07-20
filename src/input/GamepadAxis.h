#pragma once

#include "../inferno.h"

namespace inferno {
    enum class GamepadAxis {
        LEFT_X = internal::GAMEPAD_AXIS_LEFT_X,
        LEFT_Y = internal::GAMEPAD_AXIS_LEFT_Y,
        RIGHT_X = internal::GAMEPAD_AXIS_RIGHT_X,
        RIGHT_Y = internal::GAMEPAD_AXIS_RIGHT_Y,
        LEFT_TRIGGER = internal::GAMEPAD_AXIS_LEFT_TRIGGER,
        RIGHT_TRIGGER = internal::GAMEPAD_AXIS_RIGHT_TRIGGER,
    };
}
