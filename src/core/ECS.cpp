#include "ECS.h"

#include "../components/Transform.h"
#include "./Game.h"

namespace inferno {
    std::vector<System> ECS::systems_;

    ECS::ECS() = default;

    void ECS::system(const System &system) {
        Game::throw_if_initialized();
        systems_.push_back(system);
    }

    void ECS::on_update(const UpdateListener &update_listener) {
        Game::throw_if_initialized();
        update_listeners_.push_back(update_listener);
    }

    void ECS::on_ordered_update(const OrderedUpdateListener &update_listener) {
        Game::throw_if_initialized();
        ordered_update_listeners_.push_back(update_listener);
    }

    void ECS::on_fixed_update(const FixedUpdateListener &fixed_update_listener) {
        Game::throw_if_initialized();
        fixed_update_listeners_.push_back(fixed_update_listener);
    }

    Entity ECS::create() {
        const auto entity = static_cast<Entity>(registry_.create());
        auto transform = add<Transform>(entity);
        entities_to_create_.push_back(entity);
        return entity;
    }

    void ECS::destroy(Entity entity) {
        registry_.destroy(static_cast<entt::entity>(entity));
        entities_to_destroy_.push_back(entity);
    }
}
