#pragma once

#include "../inferno.h"

#include "./GamepadButton.h"
#include "./GamepadAxis.h"

using GamepadID = uint8_t;

namespace inferno {
    class Gamepad final {
    public:
        static std::vector<Gamepad *> get_gamepads();

        static Gamepad *get(GamepadID id);

        Gamepad(const Gamepad &gamepad) = delete;

        Gamepad &operator=(const Gamepad &gamepad) = delete;

        [[nodiscard]] GamepadID get_id() const;

        [[nodiscard]] bool is_connected() const;

        [[nodiscard]] std::string get_name() const;

        [[nodiscard]] std::set<GamepadButton> get_down_buttons() const;

        [[nodiscard]] std::set<GamepadButton> get_up_buttons() const;

        [[nodiscard]] std::set<GamepadButton> get_pressed_buttons() const;

        [[nodiscard]] std::set<GamepadButton> get_released_buttons() const;

        [[nodiscard]] bool is_button_down(GamepadButton button) const;

        [[nodiscard]] bool is_button_up(GamepadButton button) const;

        [[nodiscard]] bool is_button_pressed(GamepadButton button) const;

        [[nodiscard]] bool is_button_released(GamepadButton button) const;

        [[nodiscard]] std::unordered_map<GamepadAxis, float> get_axes() const;

        [[nodiscard]] float get_axis(GamepadAxis axis) const;

    private:
        explicit Gamepad(GamepadID id);

        GamepadID id_;

        bool connected_;

        std::string name_;

        std::set<GamepadButton> down_buttons_;

        std::set<GamepadButton> up_buttons_;

        std::set<GamepadButton> pressed_buttons_;

        std::set<GamepadButton> released_buttons_;

        std::unordered_map<GamepadAxis, float> axes_;

        static void update_all_();

        static void destroy_();

        void update_();

        void reset_state_();

        void update_state_();

        class Object_ final {
        public:
            std::vector<std::unique_ptr<Gamepad> > gamepads_;

            std::vector<GamepadButton> buttons_;

            std::vector<GamepadAxis> axes_;

            Object_();

            ~Object_();
        };

        static Object_ *get_();

        friend class Game;
    };
}
