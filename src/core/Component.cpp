#include "./Component.h"

namespace inferno {
    Entity *Component::get_entity() const {
        return entity_;
    }
}
