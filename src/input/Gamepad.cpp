#include "./Gamepad.h"

#include "../core/Game.h"

namespace inferno {
    std::vector<Gamepad *> Gamepad::get_gamepads() {
        const auto object = get_();
        std::vector<Gamepad *> result;
        for (const auto &gamepad : object->gamepads_) {
            result.push_back(gamepad.get());
        }
        return result;
    }

    Gamepad *Gamepad::get(const GamepadID id) {
        const auto object = get_();
        if (id < 0 || id >= object->gamepads_.size()) {
            throw std::out_of_range("Gamepad ID out of range");
        }
        return object->gamepads_[id].get();
    }

    GamepadID Gamepad::get_id() const {
        return id_;
    }

    bool Gamepad::is_connected() const {
        return connected_;
    }

    std::string Gamepad::get_name() const {
        return name_;
    }

    std::set<GamepadButton> Gamepad::get_down_buttons() const {
        return down_buttons_;
    }

    std::set<GamepadButton> Gamepad::get_up_buttons() const {
        return up_buttons_;
    }

    std::set<GamepadButton> Gamepad::get_pressed_buttons() const {
        return pressed_buttons_;
    }

    std::set<GamepadButton> Gamepad::get_released_buttons() const {
        return released_buttons_;
    }

    bool Gamepad::is_button_down(const GamepadButton button) const {
        return down_buttons_.contains(button);
    }

    bool Gamepad::is_button_up(const GamepadButton button) const {
        return up_buttons_.contains(button);
    }

    bool Gamepad::is_button_pressed(const GamepadButton button) const {
        return pressed_buttons_.contains(button);
    }

    bool Gamepad::is_button_released(const GamepadButton button) const {
        return released_buttons_.contains(button);
    }

    std::unordered_map<GamepadAxis, float> Gamepad::get_axes() const {
        return axes_;
    }

    float Gamepad::get_axis(const GamepadAxis axis) const {
        return axes_.at(axis);
    }

    Gamepad::Object_ *Gamepad::Object_::instance_ = nullptr;

    Gamepad::Object_::Object_() {
        Game::throw_if_uninitialized();
        constexpr auto nb_gamepads = 8;
        for (auto i = 0; i < nb_gamepads; i++) {
            gamepads_.emplace_back(std::unique_ptr<Gamepad>(new Gamepad(i)));
        }
        magic_enum::enum_for_each<GamepadButton>([this](const GamepadButton button) {
            buttons_.push_back(button);
        });
        magic_enum::enum_for_each<GamepadAxis>([this](const GamepadAxis axis) {
            axes_.push_back(axis);
        });
    }

    Gamepad::Object_::~Object_() {
        instance_ = nullptr;
    }

    Gamepad::Gamepad(const GamepadID id) {
        id_ = id;
        connected_ = false;
        magic_enum::enum_for_each<GamepadAxis>([this](const GamepadAxis axis) {
            axes_.insert({axis, 0.f});
        });
    }

    void Gamepad::update_all_() {
        for (const auto &gamepad : get_()->gamepads_) {
            gamepad->update_();
        }
    }

    void Gamepad::destroy_() {
        delete get_();
    }

    void Gamepad::update_() {
        reset_state_();
        update_state_();
    }

    void Gamepad::reset_state_() {
        const auto object = get_();
        connected_ = internal::IsGamepadAvailable(id_);
        name_ = "Unknown";
        down_buttons_.clear();
        up_buttons_.clear();
        pressed_buttons_.clear();
        released_buttons_.clear();
        for (auto axis : object->axes_) {
            axes_[axis] = 0.f;
        }
    }

    void Gamepad::update_state_() {
        const auto object = get_();
        if (!Game::is_focused() || !connected_) {
            for (auto button : object->buttons_) {
                up_buttons_.insert(button);
            }
            return;
        }
        name_ = internal::GetGamepadName(id_);
        for (auto button : object->buttons_) {
            const auto button_code = static_cast<int32_t>(button);
            if (internal::IsGamepadButtonDown(id_, button_code)) {
                down_buttons_.insert(button);
            } else {
                up_buttons_.insert(button);
            }
            if (internal::IsGamepadButtonPressed(id_, button_code)) {
                pressed_buttons_.insert(button);
            }
            if (internal::IsGamepadButtonReleased(id_, button_code)) {
                released_buttons_.insert(button);
            }
        }
        for (auto axis : object->axes_) {
            const auto axis_code = static_cast<int32_t>(axis);
            axes_[axis] = internal::GetGamepadAxisMovement(id_, axis_code);
        }
    }

    Gamepad::Object_ *Gamepad::get_() {
        return Object_::instance_ = Object_::instance_ == nullptr ? new Object_() : Object_::instance_;
    }
}
