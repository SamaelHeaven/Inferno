#pragma once

#include "../core/Property.h"
#include "../math/Vector2.h"

namespace inferno {
    struct Transform {
        Property<Vector2> position_property{Vector2::ZERO};
        Property<Vector2> size_property{Vector2::ZERO};
        Property<Vector2> pivot_point_property{Vector2::ZERO};
        Property<float> rotation_property{0.0f};
        Property<int32_t> z_index_property{0};

        Transform();

        [[nodiscard]] Vector2 get_position() const;

        void set_position(Vector2 position);

        [[nodiscard]] Vector2 get_size() const;

        void set_size(Vector2 size);

        [[nodiscard]] Vector2 get_pivot_point() const;

        void set_pivot_point(Vector2 pivot_point);

        [[nodiscard]] float get_rotation() const;

        void set_rotation(float rotation);

        [[nodiscard]] int get_z_index() const;

        void set_z_index(int z_index);
    };
}
