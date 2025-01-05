#include "./Scene.h"

#include "./Time.h"

namespace inferno {
    Scene::~Scene() = default;

    ECS &Scene::get_ecs() {
        return ecs_;
    }

    void Scene::initialize() {}

    void Scene::update() {}

    void Scene::initialize_() {
        if (initialized_) {
            return;
        }
        initialized_ = true;
        initialize();
        Time::restart_();
    }

    void Scene::update_() {
        update();
        for (const auto &system : ECS::systems_) {
            system(ecs_);
        }
    }
}
