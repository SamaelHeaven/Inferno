#pragma once

namespace inferno {
    enum class Platform {
        DESKTOP,
        WEB,
    };

    Platform current_platform();
}
