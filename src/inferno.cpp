#include "./inferno.h"

#undef main

void inferno_main();

int32_t main() {
    SetTraceLogLevel(inferno::internal::LOG_NONE);
    inferno_main();
    return 0;
}
