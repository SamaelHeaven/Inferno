#pragma once

#include "../core/ECS.h"
#include "../core/Game.h"
#include "../core/Property.h"
#include "../math/Vector2.h"

namespace inferno {
    struct Transform {
        Entity entity;
        Property<Vector2> position_property{Vector2::ZERO};
        Property<Vector2> size_property{Vector2::ZERO};
        Property<Vector2> pivot_point_property{Vector2::ZERO};
        Property<float> rotation_property{0};
        Property<int32_t> z_index_property{0, [&](int32_t value, auto set) {
                                               auto &ecs = Game::get_scene()->get_ecs();
                                               auto &entities = ecs.entities_;
                                               const auto range = entities.equal_range(z_index_property.get());
                                               for (auto it = range.first; it != range.second;) {
                                                   if (it->second == entity) {
                                                       it = entities.erase(it);
                                                       break;
                                                   }
                                                   ++it;
                                               }
                                               entities.emplace(value, entity);
                                               set(value);
                                           }};

        Transform();

        Transform(const Transform &other);

        Transform &operator=(const Transform &other);

        Vector2 get_position() const;

        void set_position(Vector2 position);

        Vector2 get_size() const;

        void set_size(Vector2 size);

        Vector2 get_pivot_point() const;

        void set_pivot_point(Vector2 pivot_point);

        float get_rotation() const;

        void set_rotation(float rotation);

        int get_z_index() const;

        void set_z_index(int z_index);
    };
}
