#include "Rectangle.h"

namespace inferno {
    void Rectangle::bind(Transform transform) {
        position_property.bind_bidirectional(transform.position_property);
        scale_property.bind_bidirectional(transform.scale_property);
        origin_property.bind_bidirectional(transform.origin_property);
        pivot_point_property.bind_bidirectional(transform.pivot_point_property);
        rotation_property.bind_bidirectional(transform.rotation_property);
    }

    Vector2 Rectangle::get_position() const {
        return position_property.get();
    }

    void Rectangle::set_position(const Vector2 position) {
        position_property.set(position);
    }

    Vector2 Rectangle::get_scale() const {
        return scale_property.get();
    }

    void Rectangle::set_scale(const Vector2 scale) {
        scale_property.set(scale);
    }

    Vector2 Rectangle::get_origin() const {
        return origin_property.get();
    }

    void Rectangle::set_origin(const Vector2 origin) {
        origin_property.set(origin);
    }

    Vector2 Rectangle::get_pivot_point() const {
        return pivot_point_property.get();
    }

    void Rectangle::set_pivot_point(const Vector2 pivot_point) {
        pivot_point_property.set(pivot_point);
    }

    float Rectangle::get_rotation() const {
        return rotation_property.get();
    }

    void Rectangle::set_rotation(const float rotation) {
        rotation_property.set(rotation);
    }

    Color Rectangle::get_fill() const {
        return fill_property.get();
    }

    void Rectangle::set_fill(const Color fill) {
        fill_property.set(fill);
    }

    Color Rectangle::get_stroke() const {
        return stroke_property.get();
    }

    void Rectangle::set_stroke(const Color stroke) {
        stroke_property.set(stroke);
    }

    float Rectangle::get_stroke_width() const {
        return stroke_width_property.get();
    }

    void Rectangle::set_stroke_width(const float stroke_width) {
        stroke_width_property.set(stroke_width);
    }
}
