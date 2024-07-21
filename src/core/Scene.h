#pragma once

#include "../inferno.h"

#include "./Entity.h"

namespace inferno {
    class Scene {
    public:
        virtual ~Scene() = default;

    protected:
        virtual void initialize() {}

        virtual void update() {}

        [[nodiscard]] std::shared_ptr<Entity> find_entity_by_name(const std::string &name) const;

        [[nodiscard]] std::list<std::shared_ptr<Entity> > find_entities_by_name(const std::string &name) const;

        template<typename T>
        [[nodiscard]] std::shared_ptr<T> find_entity_by_type() const {
            for (const auto &entity: entities_) {
                if (const auto component = entity->get_component<T>()) {
                    return component;
                }
            }
            return nullptr;
        }

        template<typename T>
        [[nodiscard]] std::list<std::shared_ptr<T> > find_entities_by_type() const {
            std::list<std::shared_ptr<T> > result;
            for (const auto &entity: entities_) {
                if (const auto component = entity->get_component<T>()) {
                    result.push_back(component);
                }
            }
            return result;
        }

        [[nodiscard]] std::shared_ptr<Entity> find_entity_by_tag(const std::string &tag) const;

        [[nodiscard]] std::list<std::shared_ptr<Entity> > find_entities_by_tag(const std::string &tag) const;

        [[nodiscard]] bool has_entity(const std::shared_ptr<Entity> &entity) const;

        [[nodiscard]] bool has_entity(Entity *entity) const;

        void add_entity(const std::shared_ptr<Entity> &entity);

        void add_entities(std::list<std::shared_ptr<Entity> > entities);

        void remove_entity(const std::shared_ptr<Entity> &entity);

        void remove_entity(Entity *entity);

        template<typename T>
        void remove_entities() {
            for (const auto &entity: entities_) {
                if (entity->get_component<T>()) {
                    remove_entity(entity);
                }
            }
        }

        void remove_entities(const std::list<std::shared_ptr<Entity> > &entities);

    private:
        bool initialized_ = false;
        bool is_clean_ = false;
        std::list<std::shared_ptr<Entity> > entities_;
        std::set<std::shared_ptr<Entity> > entities_to_add_;
        std::set<std::shared_ptr<Entity> > entities_to_remove_;

        void initialize_();

        void update_();

        void clean_();

        void add_pending_entities_();

        void remove_pending_entities_();

        friend class Game;

        friend class Entity;
    };
}
