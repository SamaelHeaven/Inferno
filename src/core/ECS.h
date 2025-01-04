#pragma once

#include "../inferno.h"

namespace inferno {
    using Entity = uint32_t;

    class ECS final {
    public:
        ECS(const ECS &) = delete;

        Entity create();

    private:
        entt::registry registry_;
    };
}
