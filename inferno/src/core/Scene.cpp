#include "Scene.h"

#include "Time.h"

namespace inferno {
    Scene::~Scene() = default;

    void Scene::initialize() {}

    void Scene::update() {}

    void Scene::_initialize() {
        if (_initialized) {
            return;
        }
        _initialized = true;
        Time::_restart();
        initialize();
    }

    void Scene::_update() {
        update();
    }
}
