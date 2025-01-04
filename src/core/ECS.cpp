#include "ECS.h"

namespace inferno {
    Entity ECS::create() {
        return static_cast<Entity>(registry_.create());
    }
}
