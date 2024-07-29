#include "./inferno.h"

#undef main

void inferno_main(std::list<std::string> args);

int32_t main(const int32_t argc, const char **argv) {
    SetTraceLogLevel(inferno::internal::LOG_NONE);
    std::list<std::string> args;
    for (auto i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }
    inferno_main(std::move(args));
    return 0;
}
