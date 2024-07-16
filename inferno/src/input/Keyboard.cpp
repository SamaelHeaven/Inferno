#include "./Keyboard.h"

#include "../core/Game.h"

namespace inferno {
    std::string Keyboard::get_typed_string() {
        return _get_instance()->_typed_string;
    }

    std::set<Key> Keyboard::get_down_keys() {
        return _get_instance()->_down_keys;
    }

    std::set<Key> Keyboard::get_up_keys() {
        return _get_instance()->_up_keys;
    }

    std::set<Key> Keyboard::get_pressed_keys() {
        return _get_instance()->_pressed_keys;
    }

    std::set<Key> Keyboard::get_released_keys() {
        return _get_instance()->_released_keys;
    }

    bool Keyboard::is_key_down(const Key key) {
        return _get_instance()->_down_keys.contains(key);
    }

    bool Keyboard::is_key_up(const Key key) {
        return _get_instance()->_up_keys.contains(key);
    }

    bool Keyboard::is_key_pressed(const Key key) {
        return _get_instance()->_pressed_keys.contains(key);
    }

    bool Keyboard::is_key_released(const Key key) {
        return _get_instance()->_released_keys.contains(key);
    }

    Keyboard *Keyboard::_instance = nullptr;

    Keyboard::Keyboard() {
        Game::throw_if_uninitialized();
        magic_enum::enum_for_each<Key>([this](const Key key) {
            _keys.push_back(key);
        });
    }

    Keyboard::~Keyboard() = default;

    void Keyboard::_update() {
        _reset_state();
        _update_state();
    }

    void Keyboard::_destroy() {
        delete _get_instance();
    }

    void Keyboard::_reset_state() {
        const auto keyboard = _get_instance();
        keyboard->_typed_string = std::string();
        keyboard->_down_keys.clear();
        keyboard->_up_keys.clear();
        keyboard->_pressed_keys.clear();
        keyboard->_released_keys.clear();
    }

    void Keyboard::_update_state() {
        const auto keyboard = _get_instance();
        if (!Game::is_focused()) {
            for (auto key: keyboard->_keys) {
                keyboard->_up_keys.insert(key);
            }
            return;
        }
        char charTyped;
        while ((charTyped = static_cast<char>(internal::GetCharPressed()))) {
            keyboard->_typed_string.push_back(charTyped);
        }
        for (auto key: keyboard->_keys) {
            const auto key_code = static_cast<int32_t>(key);
            if (internal::IsKeyDown(key_code)) {
                keyboard->_down_keys.insert(key);
            } else {
                keyboard->_up_keys.insert(key);
            }
            if (internal::IsKeyPressed(key_code)) {
                keyboard->_pressed_keys.insert(key);
            }
            if (internal::IsKeyReleased(key_code)) {
                keyboard->_released_keys.insert(key);
            }
        }
    }

    Keyboard *Keyboard::_get_instance() {
        return _instance = _instance == nullptr ? new Keyboard() : _instance;
    }
}
