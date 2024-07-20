#include "./Time.h"

#include "./Game.h"

namespace inferno {
    float Time::delta() {
        return get_()->delta_;
    }

    float Time::fixed_delta() {
        return get_()->fixed_delta_;
    }

    float Time::average_fps() {
        return get_()->average_fps_;
    }

    float Time::current_fps() {
        get_();
        const auto delta_time = delta();
        return delta_time <= 0.f ? 0.f : 1 / delta_time;
    }

    std::chrono::nanoseconds Time::since_start() {
        const auto time = get_();
        const auto now = std::chrono::high_resolution_clock::now();
        const auto result = now.time_since_epoch() - time->start_time_;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(result);
    }

    std::chrono::nanoseconds Time::since_launch() {
        const auto time = get_();
        const auto now = std::chrono::high_resolution_clock::now();
        const auto result = now.time_since_epoch() - time->launch_time_;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(result);
    }

    void Time::update_() {
        const auto time = get_();
        const auto time_in_seconds = static_cast<float>(since_start().count()) / 1e9f;
        time->frame_count_++;
        time->delta_ = internal::GetFrameTime();
        time->average_fps_ = time_in_seconds == 0.f ? 0.f : static_cast<float>(time->frame_count_) / time_in_seconds;
    }

    void Time::restart_() {
        const auto time = get_();
        const auto now = std::chrono::high_resolution_clock::now();
        time->start_time_ = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
        time->delta_ = 0;
        time->frame_count_ = 0;
        time->average_fps_ = 0;
    }

    void Time::destroy_() {
        delete get_();
    }

    Time::Time() {
        Game::throw_if_uninitialized();
        const auto now = std::chrono::high_resolution_clock::now();
        launch_time_ = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
        start_time_ = launch_time_;
        delta_ = 0;
        fixed_delta_ = 1 / 60.f;
        average_fps_ = 0;
        frame_count_ = 0;
    }

    Time::~Time() = default;

    Time *Time::get_() {
        static Time *instance = nullptr;
        return instance = instance == nullptr ? new Time() : instance;
    }
}
