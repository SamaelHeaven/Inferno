#pragma once

#include "../inferno.h"

namespace inferno {
    class Time final {
    public:
        static float delta();

        static float fixed_delta();

        static float average_fps();

        static float current_fps();

        static std::chrono::nanoseconds since_start();

        static std::chrono::nanoseconds since_launch();

    private:
        static Time *_instance;

        float _delta;

        float _fixed_delta;

        float _average_fps;

        uint64_t _frame_count;

        std::chrono::nanoseconds _launch_time{};

        std::chrono::nanoseconds _start_time{};

        Time();

        ~Time();

        static void _update();

        static void _restart();

        static void _destroy();

        static Time *_get_instance();

        friend class Game;

        friend class Scene;
    };
}
