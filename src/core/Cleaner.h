#pragma once

#include "../inferno.h"

namespace inferno {
    class Cleaner {
    public:
        explicit Cleaner(const std::function<void()> &callback);

        ~Cleaner();

    private:
        std::function<void()> callback_;
    };
}
