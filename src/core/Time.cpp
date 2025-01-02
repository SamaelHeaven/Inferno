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
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::duration<double>(internal::GetTime() - time->start_time_));
    }

    std::chrono::nanoseconds Time::since_launch() {
        const auto time = get_();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::duration<double>(internal::GetTime() - time->launch_time_));
    }

    Time *Time::instance_ = nullptr;

    Time::Time() {
        Game::throw_if_uninitialized();
        launch_time_ = internal::GetTime();
        start_time_ = launch_time_;
        delta_ = 0;
        fixed_delta_ = 1 / 60.f;
        average_fps_ = 0;
        frame_count_ = 0;
    }

    Time::~Time() {
        instance_ = nullptr;
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
        time->start_time_ = internal::GetTime();
        time->delta_ = 0;
        time->frame_count_ = 0;
        time->average_fps_ = 0;
    }

    void Time::destroy_() {
        delete get_();
    }

    Time *Time::get_() {
        return instance_ = instance_ == nullptr ? new Time() : instance_;
    }
}
