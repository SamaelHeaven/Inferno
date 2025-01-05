#include "Scene.h"

#include "../components/Transform.h"
#include "./Time.h"

namespace inferno {
    Scene::~Scene() = default;

    ECS &Scene::get_ecs() {
        return ecs_;
    }

    void Scene::initialize() {}

    void Scene::update() {}

    void Scene::fixed_update() {}

    void Scene::initialize_() {
        if (initialized_) {
            return;
        }
        initialized_ = true;
        for (const auto &system : ECS::systems_) {
            system(ecs_);
        }
        initialize();
        Time::restart_();
    }

    void Scene::update_() {
        update();
        for (const auto &update_listener : ecs_.update_listeners_) {
            update_listener();
        }
        for (const auto entity_to_create : ecs_.entities_to_create_) {
            ecs_.entities_.push_back(entity_to_create);
        }
        ecs_.entities_to_create_.clear();
        std::ranges::stable_sort(ecs_.entities_, [&](const Entity a, const Entity b) {
            const auto a_transform = ecs_.get<Transform>(a);
            const auto b_transform = ecs_.get<Transform>(b);
            return a_transform->get_z_index() < b_transform->get_z_index();
        });
        for (const auto entity : ecs_.entities_) {
            for (const auto &ordered_update_listener : ecs_.ordered_update_listeners_) {
                ordered_update_listener(entity);
            }
        }
        for (const auto entity_to_destroy : ecs_.entities_to_destroy_) {
            std::erase_if(ecs_.entities_, [entity_to_destroy](const Entity entity) {
                return entity == entity_to_destroy;
            });
        }
        ecs_.entities_to_destroy_.clear();
        const auto delta = Time::delta();
        const auto fixed_delta = Time::fixed_delta();
        for (time_ += delta; time_ >= fixed_delta; time_ -= fixed_delta) { // NOLINT(*-flp30-c)
            fixed_update_();
        }
    }

    void Scene::fixed_update_() {
        fixed_update();
        for (const auto &fixed_update_listener : ecs_.fixed_update_listeners_) {
            fixed_update_listener();
        }
    }
}
