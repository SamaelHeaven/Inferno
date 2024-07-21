#include "./Keyboard.h"

#include "../core/Game.h"

namespace inferno {
    std::string Keyboard::get_typed_string() {
        return get_()->typed_string_;
    }

    std::set<Key> Keyboard::get_down_keys() {
        return get_()->down_keys_;
    }

    std::set<Key> Keyboard::get_up_keys() {
        return get_()->up_keys_;
    }

    std::set<Key> Keyboard::get_pressed_keys() {
        return get_()->pressed_keys_;
    }

    std::set<Key> Keyboard::get_released_keys() {
        return get_()->released_keys_;
    }

    bool Keyboard::is_key_down(const Key key) {
        return get_()->down_keys_.contains(key);
    }

    bool Keyboard::is_key_up(const Key key) {
        return get_()->up_keys_.contains(key);
    }

    bool Keyboard::is_key_pressed(const Key key) {
        return get_()->pressed_keys_.contains(key);
    }

    bool Keyboard::is_key_released(const Key key) {
        return get_()->released_keys_.contains(key);
    }

    Keyboard *Keyboard::instance_ = nullptr;

    Keyboard::Keyboard() {
        Game::throw_if_uninitialized();
        magic_enum::enum_for_each<Key>([this](const Key key) {
            keys_.push_back(key);
        });
    }

    Keyboard::~Keyboard() {
        instance_ = nullptr;
    }

    void Keyboard::update_() {
        reset_state_();
        update_state_();
    }

    void Keyboard::destroy_() {
        delete get_();
    }

    void Keyboard::reset_state_() {
        const auto keyboard = get_();
        keyboard->typed_string_ = std::string();
        keyboard->down_keys_.clear();
        keyboard->up_keys_.clear();
        keyboard->pressed_keys_.clear();
        keyboard->released_keys_.clear();
    }

    void Keyboard::update_state_() {
        const auto keyboard = get_();
        if (!Game::is_focused()) {
            for (auto key: keyboard->keys_) {
                keyboard->up_keys_.insert(key);
            }
            return;
        }
        char charTyped;
        while ((charTyped = static_cast<char>(internal::GetCharPressed()))) {
            keyboard->typed_string_.push_back(charTyped);
        }
        for (auto key: keyboard->keys_) {
            const auto key_code = static_cast<int32_t>(key);
            if (internal::IsKeyDown(key_code)) {
                keyboard->down_keys_.insert(key);
            } else {
                keyboard->up_keys_.insert(key);
            }
            if (internal::IsKeyPressed(key_code)) {
                keyboard->pressed_keys_.insert(key);
            }
            if (internal::IsKeyReleased(key_code)) {
                keyboard->released_keys_.insert(key);
            }
        }
    }

    Keyboard *Keyboard::get_() {
        return instance_ = instance_ == nullptr ? new Keyboard() : instance_;
    }
}
