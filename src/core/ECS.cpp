#include "ECS.h"

namespace inferno {
    ECS::ECS() = default;

    void ECS::system(const System system) {
        systems_.push_back(system);
    }

    Entity ECS::create() {
        return static_cast<Entity>(registry_.create());
    }

    void ECS::destroy(Entity entity) {
        registry_.destroy(static_cast<entt::entity>(entity));
    }
}
