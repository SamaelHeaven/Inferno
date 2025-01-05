#include "Scene.h"

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
        for (const auto &update_listener : ecs_.update_listeners_) {
            update_listener();
        }
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
