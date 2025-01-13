#include "Platform.h"

namespace inferno {
    Platform current_platform() {
#ifdef PLATFORM_DESKTOP
        return Platform::DESKTOP;
#elif defined(PLATFORM_WEB)
        return Platform::WEB;
#else
        static_assert(false, "Unsupported platform");
#endif
    }
}
