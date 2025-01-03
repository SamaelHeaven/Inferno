#pragma once

#include "../inferno.h"

#include "../math/Vector2.h"
#include "./Cursor.h"
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

        static Vector2 get_position();

        static void set_position(Vector2 position);

        static Vector2 get_screen_position();

        static void set_screen_position(Vector2 position);

        static bool is_on_screen();

        static Cursor get_cursor();

        static void set_cursor(Cursor cursor);

        static Vector2 get_scroll();

    private:
        static Mouse *instance_;

        std::vector<MouseButton> buttons_;

        std::set<MouseButton> down_buttons_;

        std::set<MouseButton> up_buttons_;

        std::set<MouseButton> pressed_buttons_;

        std::set<MouseButton> released_buttons_;

        Cursor cursor_;

        Vector2 screen_position_;

        Vector2 scroll_;

        Mouse();

        ~Mouse();

        static void update_();

        static void destroy_();

        static void reset_state_();

        static void update_state_();

        static Mouse *get_();

        friend class Game;
    };
}
