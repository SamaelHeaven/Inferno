#include "Transform.h"

namespace inferno {
    Transform::Transform() = default;

    Transform::Transform(const Transform &other) {
        set_position(other.get_position());
        set_size(other.get_size());
        set_pivot_point(other.get_pivot_point());
        set_rotation(other.get_rotation());
        set_z_index(other.get_z_index());
    }

    Transform &Transform::operator=(const Transform &other) {
        set_position(other.get_position());
        set_size(other.get_size());
        set_pivot_point(other.get_pivot_point());
        set_rotation(other.get_rotation());
        set_z_index(other.get_z_index());
        return *this;
    }

    Vector2 Transform::get_position() const {
        return position_subject.get_value();
    }

    void Transform::set_position(const Vector2 position) const {
        position_subject.get_subscriber().on_next(position);
    }

    Vector2 Transform::get_size() const {
        return size_subject.get_value();
    }

    void Transform::set_size(const Vector2 size) const {
        size_subject.get_subscriber().on_next(size);
    }

    Vector2 Transform::get_pivot_point() const {
        return pivot_point_subject.get_value();
    }

    void Transform::set_pivot_point(const Vector2 pivot_point) const {
        pivot_point_subject.get_subscriber().on_next(pivot_point);
    }

    float Transform::get_rotation() const {
        return rotation_subject.get_value();
    }

    void Transform::set_rotation(const float rotation) const {
        rotation_subject.get_subscriber().on_next(rotation);
    }

    int Transform::get_z_index() const {
        return z_index_subject.get_value();
    }

    void Transform::set_z_index(const int z_index) const {
        z_index_subject.get_subscriber().on_next(z_index);
    }
}
