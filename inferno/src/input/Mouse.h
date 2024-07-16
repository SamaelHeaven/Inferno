#pragma once

#include "../inferno.h"

#include "./MouseButton.h"

namespace inferno {
    class Mouse final {
    public:
        static std::set<MouseButton> get_down_buttons();

        static std::set<MouseButton> get_up_buttons();

        static std::set<MouseButton> get_pressed_buttons();

        static std::set<MouseButton> get_released_buttons();

        static bool is_button_down(MouseButton button);

        static bool is_button_up(MouseButton button);

        static bool is_button_pressed(MouseButton button);

        static bool is_button_released(MouseButton button);

    private:
        static Mouse *_instance;

        std::vector<MouseButton> _buttons;

        std::set<MouseButton> _down_buttons;

        std::set<MouseButton> _up_buttons;

        std::set<MouseButton> _pressed_buttons;

        std::set<MouseButton> _released_buttons;

        Mouse();

        ~Mouse();

        static void _update();

        static void _destroy();

        static void _reset_state();

        static void _update_state();

        static Mouse *_get_instance();

        friend class Game;
    };
}
