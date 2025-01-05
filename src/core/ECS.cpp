#include "ECS.h"

#include "../components/Transform.h"

namespace inferno {
    std::vector<System> ECS::systems_;

    ECS::ECS() = default;

    void ECS::system(const System &system) {
        systems_.push_back(system);
    }

    void ECS::on_update(const UpdateListener &update_listener) {
        update_listeners_.push_back(update_listener);
    }

    void ECS::on_fixed_update(const FixedUpdateListener &fixed_update_listener) {
        fixed_update_listeners_.push_back(fixed_update_listener);
    }

    Entity ECS::create() {
        const auto entity = static_cast<Entity>(registry_.create());
        add<Transform>(entity);
        entities_.emplace(0, entity);
        return entity;
    }

    void ECS::destroy(Entity entity) {
        registry_.destroy(static_cast<entt::entity>(entity));
    }
}
