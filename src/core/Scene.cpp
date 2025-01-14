#include "Scene.h"

#include "./Game.h"
#include "./Time.h"
#include "./Transform.h"

namespace inferno {
    Scene::~Scene() = default;

    std::shared_ptr<Scene> Scene::current() {
        return Game::get_scene();
    }

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
        auto &entities = ecs_.entities_;
        auto &entities_to_create = ecs_.entities_to_create_;
        auto &entities_to_destroy = ecs_.entities_to_destroy_;
        for (const auto &update_listener : ecs_.update_listeners_) {
            update_listener();
        }
        for (const auto entity_to_create : entities_to_create) {
            const auto transform = ecs_.get<Transform>(entity_to_create);
            entities.emplace_back(&transform->z_index_property.get(), entity_to_create);
        }
        entities_to_create.clear();
        std::ranges::stable_sort(entities, [](const auto &a, const auto &b) {
            return *a.first < *b.first;
        });
        for (const auto [z_index, entity] : entities) {
            for (const auto &ordered_update_listener : ecs_.ordered_update_listeners_) {
                ordered_update_listener(entity);
            }
        }
        std::erase_if(entities, [&](const auto &entry) {
            return std::find(entities_to_destroy.begin(), entities_to_destroy.end(), entry.second) !=
                entities_to_destroy.end();
        });
        entities_to_destroy.clear();
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
