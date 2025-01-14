#include "Transform.h"

namespace inferno {
    Vector2 Transform::get_position() const {
        return position_property.get();
    }

    void Transform::set_position(const Vector2 position) {
        position_property.set(position);
    }

    Vector2 Transform::get_scale() const {
        return scale_property.get();
    }

    void Transform::set_scale(const Vector2 scale) {
        scale_property.set(scale);
    }

    Vector2 Transform::get_origin() const {
        return origin_property.get();
    }

    void Transform::set_origin(const Vector2 origin) {
        origin_property.set(origin);
    }

    Vector2 Transform::get_pivot_point() const {
        return pivot_point_property.get();
    }

    void Transform::set_pivot_point(const Vector2 pivot_point) {
        pivot_point_property.set(pivot_point);
    }

    float Transform::get_rotation() const {
        return rotation_property.get();
    }

    void Transform::set_rotation(const float rotation) {
        rotation_property.set(rotation);
    }

    int Transform::get_z_index() const {
        return z_index_property.get();
    }

    void Transform::set_z_index(const int z_index) {
        z_index_property.set(z_index);
    }
}
