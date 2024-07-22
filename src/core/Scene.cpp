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
        initialize();
        Time::restart_();
        initialized_ = true;
    }

    void Scene::update_() {
        update();
    }
}
