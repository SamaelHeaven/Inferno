#pragma once

#include "../components/Transform.h"
#include "../core/Property.h"
#include "../math/Vector2.h"
#include "Color.h"

namespace inferno {
    struct Rectangle {
        Property<Vector2> position_property{Vector2::ZERO};
        Property<Vector2> scale_property{Vector2::ZERO};
        Property<Vector2> origin_property{Vector2::ZERO};
        Property<Vector2> pivot_point_property{Vector2::ZERO};
        Property<float> rotation_property{0};
        Property<Color> fill_property{Color::TRANSPARENT};
        Property<Color> stroke_property{Color::TRANSPARENT};
        Property<float> stroke_width_property{1};
        Property<float> radius_property{0};

        Rectangle();

        explicit Rectangle(const Transform &transform);

        void bind(const Transform &transform);

        [[nodiscard]] Vector2 get_position() const;

        void set_position(Vector2 position);

        [[nodiscard]] Vector2 get_scale() const;

        void set_scale(Vector2 scale);

        [[nodiscard]] Vector2 get_origin() const;

        void set_origin(Vector2 origin);

        [[nodiscard]] Vector2 get_pivot_point() const;

        void set_pivot_point(Vector2 pivot_point);

        [[nodiscard]] float get_rotation() const;

        void set_rotation(float rotation);

        [[nodiscard]] Color get_fill() const;

        void set_fill(Color fill);

        [[nodiscard]] Color get_stroke() const;

        void set_stroke(Color stroke);

        [[nodiscard]] float get_stroke_width() const;

        void set_stroke_width(float stroke_width);

        [[nodiscard]] float get_radius() const;

        void set_radius(float radius);
    };
}
