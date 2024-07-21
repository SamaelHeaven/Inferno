#include "./Entity.h"

#include "./Game.h"

namespace inferno {
    Entity::Entity(std::string name): name(std::move(name)) {}

    Vector2 Entity::get_position() const {
        return position_property.get();
    }

    void Entity::set_position(const Vector2 position) {
        position_property.set(position);
    }

    Vector2 Entity::get_size() const {
        return size_property.get();
    }

    void Entity::set_size(const Vector2 size) {
        size_property.set(size);
    }

    Vector2 Entity::get_pivot_point() const {
        return pivot_point_property.get();
    }

    void Entity::set_pivot_point(const Vector2 pivot_point) {
        pivot_point_property.set(pivot_point);
    }

    Vector2 Entity::get_origin() const {
        return origin_property.get();
    }

    void Entity::set_origin(const Vector2 origin) {
        origin_property.set(origin);
    }

    float Entity::get_rotation() const {
        return rotation_property.get();
    }

    void Entity::set_rotation(const float rotation) {
        rotation_property.set(rotation);
    }

    int Entity::get_z_index() const {
        return z_index_property.get();
    }

    void Entity::set_z_index(const int z_index) {
        z_index_property.set(z_index);
    }

    std::list<std::shared_ptr<Component> > Entity::get_components() const {
        return components_;
    }

    bool Entity::has_component(const std::shared_ptr<Component> &component) const {
        return has_component(component.get());
    }

    bool Entity::has_component(Component *const component) const {
        const auto found_component = std::ranges::find_if(
            components_,
            [&component](const std::shared_ptr<Component> &element) {
                return element.get() == component;
            }
        );
        return found_component != components_.end();
    }

    void Entity::add_component(const std::shared_ptr<Component> &component) {
        if (has_component(component)) {
            return;
        }
        if (component->entity_ != nullptr) {
            throw std::runtime_error("A component cannot be attached to multiple entities");
        }
        components_to_add_.insert(component);
        is_clean_ = false;
        if (is_scene_initialized_()) {
            return;
        }
        clean_();
    }

    void Entity::add_components(const std::list<std::shared_ptr<Component> > &components) {
        for (const auto &component: components) {
            add_component(component);
        }
    }

    void Entity::remove_component(const std::shared_ptr<Component> &component) {
        if (!has_component(component) && !components_to_add_.contains(component)) {
            return;
        }
        components_to_remove_.insert(component);
        is_clean_ = false;
        if (is_scene_initialized_()) {
            return;
        }
        clean_();
    }

    void Entity::remove_component(Component *component) {
        if (const auto found_component = std::ranges::find_if(
            components_,
            [component](const std::shared_ptr<Component> &element) {
                return element.get() == component;
            }
        ); found_component != components_.end()) {
            remove_component(*found_component);
        }
    }

    void Entity::remove_components(const std::list<std::shared_ptr<Component> > &components) {
        for (const auto &component: components) {
            remove_component(component);
        }
    }

    bool Entity::is_scene_initialized_() {
        return Game::get_scene()->initialized_;
    }

    void Entity::start_() {
        auto &components = components_;
        if (!is_scene_initialized_()) {
            components = get_components();
        }
        for (const auto &component: components) {
            component->start();
        }
        clean_();
    }

    void Entity::update_() {
        for (const auto &component: components_) {
            component->update();
        }
        clean_();
    }

    void Entity::fixed_update_() {
        for (const auto &component: components_) {
            component->fixed_update();
        }
        clean_();
    }

    void Entity::destroy_() {
        auto &components = components_;
        if (!is_scene_initialized_()) {
            components = get_components();
        }
        for (const auto &component: components) {
            component->destroy();
        }
        clean_();
    }

    void Entity::clean_() {
        if (is_clean_) {
            return;
        }
        do {
            is_clean_ = true;
            add_pending_components_();
            remove_pending_components_();
        } while (!is_clean_);
    }

    void Entity::add_pending_components_() {
        const std::set components_too_add(components_to_add_.begin(), components_to_add_.end());
        components_.insert(components_.end(), components_too_add.begin(), components_too_add.end());
        for (const auto &component: components_too_add) {
            component->entity_ = this;
            if (Game::get_scene()->has_entity(this)) {
                component->start();
            }
            components_to_add_.erase(component);
        }
    }

    void Entity::remove_pending_components_() {
        for (const std::set components_to_remove(
                 components_to_remove_.begin(),
                 components_to_remove_.end()
             ); const auto &component: components_to_remove
        ) {
            components_.remove(component);
            component->destroy();
            component->entity_ = nullptr;
            components_to_remove_.erase(component);
        }
    }
}
