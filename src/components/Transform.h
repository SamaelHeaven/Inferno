#pragma once

#include "../math/Vector2.h"

namespace inferno {
    struct Transform {
        const rxcpp::subjects::behavior<Vector2> position_subject{Vector2::ZERO};
        const rxcpp::subjects::behavior<Vector2> size_subject{Vector2::ZERO};
        const rxcpp::subjects::behavior<Vector2> pivot_point_subject{Vector2::ZERO};
        const rxcpp::subjects::behavior<float> rotation_subject{0.0f};
        const rxcpp::subjects::behavior<int32_t> z_index_subject{0};

        Transform();

        Transform(const Transform &other);

        Transform &operator=(const Transform &other);

        [[nodiscard]] Vector2 get_position() const;

        void set_position(Vector2 position) const;

        [[nodiscard]] Vector2 get_size() const;

        void set_size(Vector2 size) const;

        [[nodiscard]] Vector2 get_pivot_point() const;

        void set_pivot_point(Vector2 pivot_point) const;

        [[nodiscard]] float get_rotation() const;

        void set_rotation(float rotation) const;

        [[nodiscard]] int get_z_index() const;

        void set_z_index(int z_index) const;
    };
}
