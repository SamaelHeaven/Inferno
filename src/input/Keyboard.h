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
        std::string typed_string_;

        std::vector<Key> keys_;

        std::set<Key> down_keys_;

        std::set<Key> up_keys_;

        std::set<Key> pressed_keys_;

        std::set<Key> released_keys_;

        Keyboard();

        ~Keyboard();

        static void update_();

        static void destroy_();

        static void reset_state_();

        static void update_state_();

        static Keyboard *get_();

        friend class Game;
    };
}
