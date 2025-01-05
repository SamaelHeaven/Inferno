#pragma once

#include "../math/Vector2.h"
#include "./Property.h"

namespace inferno {
    struct Transform {
        Property<Vector2> position_property{Vector2::ZERO};
        Property<Vector2> size_property{Vector2::ZERO};
        Property<Vector2> pivot_point_property{Vector2::ZERO};
        Property<float> rotation_property{0};
        Property<int> z_index_property{0};

        Vector2 get_position() const {
            return position_property.get();
        }

        void set_position(const Vector2 position) {
            position_property.set(position);
        }

        Vector2 get_size() const {
            return size_property.get();
        }

        void set_size(const Vector2 size) {
            size_property.set(size);
        }

        Vector2 get_pivot_point() const {
            return pivot_point_property.get();
        }

        void set_pivot_point(const Vector2 pivot_point) {
            pivot_point_property.set(pivot_point);
        }

        float get_rotation() const {
            return rotation_property.get();
        }

        void set_rotation(const float rotation) {
            rotation_property.set(rotation);
        }

        int get_z_index() const {
            return z_index_property.get();
        }

        void set_z_index(const int z_index) {
            z_index_property.set(z_index);
        }
    };
}
