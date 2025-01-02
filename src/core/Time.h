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
        static Time *instance_;

        float delta_;

        float fixed_delta_;

        float average_fps_;

        uint64_t frame_count_;

        std::chrono::nanoseconds launch_time_{};

        std::chrono::nanoseconds start_time_{};

        Time();

        ~Time();

        static void update_();

        static void restart_();

        static void destroy_();

        static Time *get_();

        friend class Game;

        friend class Scene;
    };
}
