#include "./Mouse.h"

#include "../core/Game.h"
#include "../math/coordinates.h"

namespace inferno {
    std::set<MouseButton> Mouse::get_down_buttons() {
        return _get_instance()->_down_buttons;
    }

    std::set<MouseButton> Mouse::get_up_buttons() {
        return _get_instance()->_up_buttons;
    }

    std::set<MouseButton> Mouse::get_pressed_buttons() {
        return _get_instance()->_pressed_buttons;
    }

    std::set<MouseButton> Mouse::get_released_buttons() {
        return _get_instance()->_released_buttons;
    }

    bool Mouse::is_button_down(const MouseButton button) {
        return _get_instance()->_down_buttons.contains(button);
    }

    bool Mouse::is_button_up(const MouseButton button) {
        return _get_instance()->_up_buttons.contains(button);
    }

    bool Mouse::is_button_pressed(const MouseButton button) {
        return _get_instance()->_pressed_buttons.contains(button);
    }

    bool Mouse::is_button_released(const MouseButton button) {
        return _get_instance()->_released_buttons.contains(button);
    }

    Vector2 Mouse::get_position() {
        _get_instance();
        return coordinates::screen_to_local(get_screen_position()).clamp(Vector2::ZERO, Game::get_size()).round();
    }

    void Mouse::set_position(Vector2 position) {
        _get_instance();
        position = position.clamp(Vector2::ZERO, Game::get_size().round());
        if (get_position() == position) {
            return;
        }
        set_screen_position(coordinates::local_to_screen(position));
    }

    Vector2 Mouse::get_screen_position() {
        return _get_instance()->_screen_position;
    }

    void Mouse::set_screen_position(Vector2 position) {
        const auto mouse = _get_instance();
        if (!Game::is_focused()) {
            return;
        }
        position = position.clamp(Vector2::ZERO, Game::get_screen_size()).round();
        if (mouse->_screen_position == position) {
            return;
        }
        mouse->_screen_position = position;
        internal::SetMousePosition(static_cast<int32_t>(position.x), static_cast<int32_t>(position.y));
    }

    bool Mouse::is_on_screen() {
        _get_instance();
        return internal::IsCursorOnScreen();
    }

    Mouse::Mouse() {
        Game::throw_if_uninitialized();
        magic_enum::enum_for_each<MouseButton>([this](const MouseButton key) {
            _buttons.push_back(key);
        });
    }

    Mouse::~Mouse() = default;

    void Mouse::_update() {
        _reset_state();
        _update_state();
    }

    void Mouse::_destroy() {
        delete _get_instance();
    }

    void Mouse::_reset_state() {
        const auto mouse = _get_instance();
        mouse->_down_buttons.clear();
        mouse->_up_buttons.clear();
        mouse->_pressed_buttons.clear();
        mouse->_released_buttons.clear();
    }

    void Mouse::_update_state() {
        const auto mouse = _get_instance();
        if (!Game::is_focused()) {
            for (auto button: mouse->_buttons) {
                mouse->_up_buttons.insert(button);
            }
            return;
        }
        mouse->_screen_position = Vector2(
            internal::GetMouseX(),
            internal::GetMouseY()
        ).clamp(Vector2::ZERO, Game::get_screen_size()).round();
        for (auto button: mouse->_buttons) {
            const auto button_code = static_cast<int32_t>(button);
            if (internal::IsMouseButtonDown(button_code)) {
                mouse->_down_buttons.insert(button);
            } else {
                mouse->_up_buttons.insert(button);
            }
            if (internal::IsMouseButtonPressed(button_code)) {
                mouse->_pressed_buttons.insert(button);
            }
            if (internal::IsMouseButtonReleased(button_code)) {
                mouse->_released_buttons.insert(button);
            }
        }
    }

    Mouse *Mouse::_get_instance() {
        static Mouse *instance = nullptr;
        return instance = instance == nullptr ? new Mouse() : instance;
    }
}
