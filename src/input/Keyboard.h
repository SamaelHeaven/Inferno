#pragma once

#include "../inferno.h"

#include "./Key.h"

namespace inferno {
    class Keyboard final {
    public:
        static std::string get_typed_string();

        static std::set<Key> get_down_keys();

        static std::set<Key> get_up_keys();

        static std::set<Key> get_pressed_keys();

        static std::set<Key> get_released_keys();

        static bool is_key_down(Key key);

        static bool is_key_up(Key key);

        static bool is_key_pressed(Key key);

        static bool is_key_released(Key key);

    private:
        static Keyboard *_instance;

        std::string _typed_string;

        std::vector<Key> _keys;

        std::set<Key> _down_keys;

        std::set<Key> _up_keys;

        std::set<Key> _pressed_keys;

        std::set<Key> _released_keys;

        Keyboard();

        ~Keyboard();

        static void _update();

        static void _destroy();

        static void _reset_state();

        static void _update_state();

        static Keyboard *_get_instance();

        friend class Game;
    };
}
