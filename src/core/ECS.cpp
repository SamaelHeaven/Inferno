#include "ECS.h"

namespace inferno {
    ECS::ECS() = default;

    Entity ECS::create() {
        return static_cast<Entity>(registry_.create());
    }
}
