#pragma once

#include "../inferno.h"

#include "./GamepadButton.h"
#include "./GamepadAxis.h"

namespace inferno {
    class Gamepad final {
    public:
        static std::vector<std::shared_ptr<Gamepad> > get_gamepads();

        static std::shared_ptr<Gamepad> get(int32_t id);

        Gamepad(const Gamepad &gamepad) = delete;

        Gamepad &operator=(const Gamepad &gamepad) = delete;

        [[nodiscard]] int32_t get_id() const;

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
        explicit Gamepad(int32_t id);

        int32_t id_;

        bool connected_;

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

        class Object final {
        public:
            std::vector<std::shared_ptr<Gamepad> > gamepads_;

            std::vector<GamepadButton> buttons_;

            std::vector<GamepadAxis> axes_;

            Object();

            ~Object();
        };

        static Object *get_();

        friend class Game;
    };
}
