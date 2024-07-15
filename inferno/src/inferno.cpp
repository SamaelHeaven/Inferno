#include "inferno.h"

#undef main

void inferno_main();

int main() {
    SetTraceLogLevel(inferno::internal::LOG_NONE);
    inferno_main();
}
