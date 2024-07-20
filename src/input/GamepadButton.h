#pragma once

#include "../inferno.h"

namespace inferno {
    enum class GamepadButton {
        DPAD_UP = internal::GAMEPAD_BUTTON_LEFT_FACE_UP,
        DPAD_RIGHT = internal::GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
        DPAD_DOWN = internal::GAMEPAD_BUTTON_LEFT_FACE_DOWN,
        DPAD_LEFT = internal::GAMEPAD_BUTTON_LEFT_FACE_LEFT,
        Y = internal::GAMEPAD_BUTTON_RIGHT_FACE_UP,
        X = internal::GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
        A = internal::GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
        B = internal::GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
        LEFT_BUMBER = internal::GAMEPAD_BUTTON_LEFT_TRIGGER_1,
        LEFT_TRIGGER = internal::GAMEPAD_BUTTON_LEFT_TRIGGER_2,
        RIGHT_BUMBER = internal::GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
        RIGHT_TRIGGER = internal::GAMEPAD_BUTTON_RIGHT_TRIGGER_2,
        OPTIONS = internal::GAMEPAD_BUTTON_MIDDLE_LEFT,
        MENU = internal::GAMEPAD_BUTTON_MIDDLE,
        START = internal::GAMEPAD_BUTTON_MIDDLE_RIGHT,
        LEFT_THUMB = internal::GAMEPAD_BUTTON_LEFT_THUMB,
        RIGHT_THUMB = internal::GAMEPAD_BUTTON_RIGHT_THUMB,
    };
}
