#include "./InputAxis.h"

#include "./Gamepad.h"
#include "./Keyboard.h"

namespace inferno {
    const InputAxis InputAxis::HORIZONTAL = InputAxis(Key::LEFT, Key::A, Key::RIGHT, Key::D, GamepadAxis::LEFT_X);
    const InputAxis InputAxis::VERTICAL = InputAxis(Key::UP, Key::W, Key::DOWN, Key::S, GamepadAxis::LEFT_Y);

    InputAxis::InputAxis(const std::optional<Key> &minus_key, const std::optional<Key> &minus_key_alt,
        const std::optional<Key> &plus_key, const std::optional<Key> &plus_key_alt,
        const std::optional<GamepadAxis> &gamepad_axis, const std::optional<GamepadID> &gamepad) {
        this->minus_key = minus_key;
        this->minus_key_alt = minus_key_alt;
        this->plus_key = plus_key;
        this->plus_key_alt = plus_key_alt;
        this->gamepad_axis = gamepad_axis;
        this->gamepad = gamepad;
    }

    Vector2 InputAxis::get_both() {
        return {HORIZONTAL.get(), VERTICAL.get()};
    }

    int InputAxis::get() const {
        auto axis = 0;
        if (gamepad.has_value() && gamepad_axis.has_value()) {
            axis = static_cast<int32_t>(std::round(Gamepad::get(gamepad.value())->get_axis(gamepad_axis.value())));
        }
        const auto minus = (minus_key.has_value() && Keyboard::is_key_down(minus_key.value())) ||
            (minus_key_alt.has_value() && Keyboard::is_key_down(minus_key_alt.value())) || axis == -1;
        const auto plus = (plus_key.has_value() && Keyboard::is_key_down(plus_key.value())) ||
            (plus_key_alt.has_value() && Keyboard::is_key_down(plus_key_alt.value())) || axis == 1;
        if (minus && !plus) {
            return -1;
        }
        if (plus && !minus) {
            return 1;
        }
        return 0;
    }
}
