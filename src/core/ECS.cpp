#include "ECS.h"

#include "./Transform.h"

namespace inferno {
    std::vector<System> ECS::systems_;

    ECS::ECS() = default;

    void ECS::system(const System &system) {
        systems_.push_back(system);
    }

    Entity ECS::create() {
        const auto entity = static_cast<Entity>(registry_.create());
        add<Transform>(entity);
        return entity;
    }

    void ECS::destroy(Entity entity) {
        registry_.destroy(static_cast<entt::entity>(entity));
    }
}
