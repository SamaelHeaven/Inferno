#include "./Component.h"

namespace inferno {
    Component::~Component() = default;

    void Component::start() {}

    void Component::update() {}

    void Component::fixed_update() {}

    void Component::destroy() {}

    Entity *Component::get_entity() const {
        return entity_;
    }
}
