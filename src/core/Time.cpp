#include "./Time.h"

#include "./Game.h"

namespace inferno {
    float Time::delta() {
        return _get_instance()->_delta;
    }

    float Time::fixed_delta() {
        return _get_instance()->_fixed_delta;
    }

    float Time::average_fps() {
        return _get_instance()->_average_fps;
    }

    float Time::current_fps() {
        _get_instance();
        const auto delta_time = delta();
        return delta_time <= 0.f ? 0.f : 1 / delta_time;
    }

    std::chrono::nanoseconds Time::since_start() {
        const auto time = _get_instance();
        const auto now = std::chrono::high_resolution_clock::now();
        const auto result = now.time_since_epoch() - time->_start_time;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(result);
    }

    std::chrono::nanoseconds Time::since_launch() {
        const auto time = _get_instance();
        const auto now = std::chrono::high_resolution_clock::now();
        const auto result = now.time_since_epoch() - time->_launch_time;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(result);
    }

    void Time::_update() {
        const auto time = _get_instance();
        const auto time_in_seconds = static_cast<float>(since_start().count()) / 1e9f;
        time->_frame_count++;
        time->_delta = internal::GetFrameTime();
        time->_average_fps = time_in_seconds == 0.f ? 0.f : static_cast<float>(time->_frame_count) / time_in_seconds;
    }

    void Time::_restart() {
        const auto time = _get_instance();
        const auto now = std::chrono::high_resolution_clock::now();
        time->_start_time = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
        time->_delta = 0;
        time->_frame_count = 0;
        time->_average_fps = 0;
    }

    void Time::_destroy() {
        delete _get_instance();
    }

    Time::Time() {
        Game::throw_if_uninitialized();
        const auto now = std::chrono::high_resolution_clock::now();
        _launch_time = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
        _start_time = _launch_time;
        _delta = 0;
        _fixed_delta = 1 / 60.f;
        _average_fps = 0;
        _frame_count = 0;
    }

    Time::~Time() = default;

    Time *Time::_get_instance() {
        static Time *instance = nullptr;
        return instance = instance == nullptr ? new Time() : instance;
    }
}
