#include "./inferno.h"

#undef main

int32_t inferno_main(const std::vector<std::string> &args);

int32_t main(const int32_t argc, const char **argv) {
    SetTraceLogLevel(inferno::internal::LOG_NONE);
    std::vector<std::string> args;
    for (auto i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }
    return inferno_main(args);
}
