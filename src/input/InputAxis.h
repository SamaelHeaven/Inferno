#pragma once

#include "../inferno.h"

#include "../math/Vector2.h"
#include "./Gamepad.h"
#include "./GamepadAxis.h"
#include "./Key.h"

namespace inferno {
    struct InputAxis final {
        const static InputAxis HORIZONTAL;
        const static InputAxis VERTICAL;

        std::optional<Key> minus_key;
        std::optional<Key> minus_key_alt;
        std::optional<Key> plus_key;
        std::optional<Key> plus_key_alt;
        std::optional<GamepadAxis> gamepad_axis;
        std::optional<GamepadID> gamepad;

        explicit InputAxis(const std::optional<Key> &minus_key = std::optional<Key>{},
            const std::optional<Key> &minus_key_alt = std::optional<Key>{},
            const std::optional<Key> &plus_key = std::optional<Key>{},
            const std::optional<Key> &plus_key_alt = std::optional<Key>{},
            const std::optional<GamepadAxis> &gamepad_axis = std::optional<GamepadAxis>{},
            const std::optional<GamepadID> &gamepad = 0);

        static Vector2 get_both();

        [[nodiscard]] int32_t get() const;
    };
}
