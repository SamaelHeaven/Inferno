#include "./Scene.h"

#include "./Time.h"

namespace inferno {
    Scene::~Scene() = default;

    void Scene::initialize() {}

    void Scene::update() {}

    void Scene::initialize_() {
        if (initialized_) {
            return;
        }
        initialized_ = true;
        Time::restart_();
        initialize();
    }

    void Scene::update_() {
        update();
    }
}
