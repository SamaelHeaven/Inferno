#pragma once

#include "../inferno.h"

#include "./Component.h"
#include "./Property.h"
#include "./Game.h"
#include "../math/Vector2.h"

namespace inferno {
    class Entity final {
    public:
        const std::string name;
        Property<Vector2> position_property{Vector2::ZERO};
        Property<Vector2> size_property{Vector2::ZERO};
        Property<Vector2> pivot_point_property{Vector2::ZERO};
        Property<float> rotation_property{0};
        Property<int> z_index_property{0};
        std::set<std::string> tags;

        Property<Vector2> origin_property{
            Vector2::ZERO, [](const Vector2 value, const auto set) {
                set(value.clamp(-1, 1));
            }
        };

        explicit Entity(std::string name = "");

        Entity(const Entity &entity) = delete;

        Entity &operator=(const Entity &entity) = delete;

        static bool sort(const std::shared_ptr<Entity> &a, const std::shared_ptr<Entity> &b) {
            return a->get_z_index() > b->get_z_index();
        }

        [[nodiscard]] Vector2 get_position() const;

        void set_position(Vector2 position);

        [[nodiscard]] Vector2 get_size() const;

        void set_size(Vector2 size);

        [[nodiscard]] Vector2 get_pivot_point() const;

        void set_pivot_point(Vector2 pivot_point);

        [[nodiscard]] Vector2 get_origin() const;

        void set_origin(Vector2 origin);

        [[nodiscard]] float get_rotation() const;

        void set_rotation(float rotation);

        [[nodiscard]] int get_z_index() const;

        void set_z_index(int z_index);

        template<typename T>
        [[nodiscard]] std::shared_ptr<T> get_component() const {
            for (const auto &component: components_) {
                if (const auto typed_component = std::dynamic_pointer_cast<T>(component)) {
                    return typed_component;
                }
            }
            return nullptr;
        }

        [[nodiscard]] std::list<std::shared_ptr<Component> > get_components() const;

        template<typename T>
        [[nodiscard]] std::list<std::shared_ptr<T> > get_components() const {
            std::list<std::shared_ptr<T> > result;
            for (const auto &component: components_) {
                if (const auto typed_component = std::dynamic_pointer_cast<T>(component)) {
                    result.push_back(typed_component);
                }
            }
            return result;
        }

        [[nodiscard]] bool has_component(const std::shared_ptr<Component> &component) const;

        [[nodiscard]] bool has_component(Component *component) const;

        void add_component(const std::shared_ptr<Component> &component);

        template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Component, T> >* = nullptr,
            std::enable_if_t<std::is_constructible_v<T, Args...> >* = nullptr>
        void add_component(Args... args) {
            add_component(std::make_shared<T>(args...));
        }

        void add_components(const std::list<std::shared_ptr<Component> > &components);

        void remove_component(const std::shared_ptr<Component> &component);

        void remove_component(Component *component);

        void remove_components(const std::list<std::shared_ptr<Component> > &components);

        template<typename T>
        void remove_components() {
            for (const auto &component: components_) {
                if (const auto typed_component = std::dynamic_pointer_cast<T>(component)) {
                    components_to_remove_.insert(component);
                }
            }
            is_clean_ = false;
            if (Game::get_scene()->initialized_) {
                return;
            }
            clean_();
        }

    private:
        std::list<std::shared_ptr<Component> > components_;
        std::set<std::shared_ptr<Component> > components_to_add_;
        std::set<std::shared_ptr<Component> > components_to_remove_;
        bool is_clean_ = false;

        void start_();

        void update_();

        void fixed_update_();

        void destroy_();

        void clean_();

        void add_pending_components_();

        void remove_pending_components_();

        friend class Scene;
    };
}
