#include "inferno.h"

#include "./core/ECS.h"
#include "./drawing/Graphics.h"
#include "./drawing/Rectangle.h"

#undef main

void inferno_main(const std::vector<std::string> &args);

int32_t main(const int32_t argc, const char **argv) {
    SetTraceLogLevel(inferno::internal::LOG_NONE);
    std::vector<std::string> args(argc);
    for (auto i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    inferno::ECS::system([](inferno::ECS &ecs) {
        using namespace inferno;

        const auto &graphics = Graphics::current();

        ecs.each<Rectangle>([&](const Rectangle &rectangle) {
            graphics.draw_rectangle(rectangle);
        });
    });

    inferno_main(args);
}
