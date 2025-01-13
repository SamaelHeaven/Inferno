#include "Cleaner.h"

namespace inferno {
    Cleaner::Cleaner(const std::function<void()> &callback) {
        callback_ = callback;
    }

    Cleaner::~Cleaner() {
        std::cout << "Destroy" << std::endl;
        callback_();
    }
}
