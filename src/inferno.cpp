#include "inferno.h"

#include "./core/ECS.h"
#include "./drawing/Graphics.h"

#undef main

using namespace inferno;

void inferno_main(const std::vector<std::string> &args);

int32_t main(const int32_t argc, const char **argv) {
    SetTraceLogLevel(internal::LOG_NONE);
    std::vector<std::string> args(argc);
    for (auto i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }
    ECS::system(Graphics::system);
    inferno_main(args);
}
