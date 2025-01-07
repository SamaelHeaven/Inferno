#include "ECS.h"

#include "./Game.h"

namespace inferno {
    std::unordered_map<const entt::registry *, ECS *> ecs_map_;

    std::vector<System> ECS::systems_;

    ECS::ECS() {
        ecs_map_[&registry_] = this;
    }

    ECS::~ECS() {
        ecs_map_.erase(&registry_);
    }

    void ECS::system(const System &system) {
        Game::throw_if_initialized();
        systems_.push_back(system);
    }

    void ECS::on_update(const UpdateListener &update_listener) {
        update_listeners_.push_back(update_listener);
    }

    void ECS::on_ordered_update(const OrderedUpdateListener &update_listener) {
        ordered_update_listeners_.push_back(update_listener);
    }

    void ECS::on_fixed_update(const FixedUpdateListener &fixed_update_listener) {
        fixed_update_listeners_.push_back(fixed_update_listener);
    }

    Entity ECS::create() {
        const auto entity = static_cast<Entity>(registry_.create());
        auto transform = registry_.emplace<Transform>(static_cast<entt::entity>(entity));
        entities_to_create_.push_back(entity);
        return entity;
    }

    void ECS::destroy(Entity entity) {
        registry_.destroy(static_cast<entt::entity>(entity));
        std::erase(entities_to_create_, entity);
        entities_to_destroy_.push_back(entity);
    }
}
