#include "./Scene.h"

#include "./Time.h"

namespace inferno {
    std::shared_ptr<Entity> Scene::find_entity_by_name(const std::string &name) const {
        for (const auto &entity: entities_) {
            if (entity->name == name) {
                return entity;
            }
        }
        return nullptr;
    }

    std::list<std::shared_ptr<Entity> > Scene::find_entities_by_name(const std::string &name) const {
        std::list<std::shared_ptr<Entity> > result;
        for (const auto &entity: entities_) {
            if (entity->name == name) {
                result.push_back(entity);
            }
        }
        return result;
    }

    std::shared_ptr<Entity> Scene::find_entity_by_tag(const std::string &tag) const {
        for (const auto &entity: entities_) {
            if (entity->tags.contains(tag)) {
                return entity;
            }
        }
        return nullptr;
    }

    std::list<std::shared_ptr<Entity> > Scene::find_entities_by_tag(const std::string &tag) const {
        std::list<std::shared_ptr<Entity> > result;
        for (const auto &entity: entities_) {
            if (entity->tags.contains(tag)) {
                result.push_back(entity);
            }
        }
        return result;
    }

    bool Scene::has_entity(const std::shared_ptr<Entity> &entity) const {
        return has_entity(entity.get());
    }

    bool Scene::has_entity(Entity *entity) const {
        const auto found_entity = std::ranges::find_if(
            entities_,
            [&entity](const std::shared_ptr<Entity> &element) {
                return element.get() == entity;
            }
        );
        return found_entity != entities_.end();
    }

    void Scene::add_entity(const std::shared_ptr<Entity> &entity) {
        if (has_entity(entity)) {
            return;
        }
        if (!initialized_) {
            entities_.push_back(entity);
            entity->start_();
            return;
        }
        entities_to_add_.insert(entity);
        is_clean_ = false;
    }

    void Scene::add_entities(std::list<std::shared_ptr<Entity> > entities) {
        entities.sort(Entity::sort);
        if (initialized_) {
            for (const auto &entity: entities) {
                entities_to_add_.insert(entity);
            }
            is_clean_ = false;
            return;
        }
        for (const auto &entity: entities) {
            entities_.push_back(entity);
        }
        for (const auto &entity: entities) {
            entity->start_();
        }
    }

    void Scene::remove_entity(const std::shared_ptr<Entity> &entity) {
        if (!has_entity(entity) || !entities_to_add_.contains(entity)) {
            return;
        }
        if (!initialized_) {
            entities_.remove(entity);
            entity->destroy_();
            return;
        }
        entities_to_remove_.insert(entity);
        is_clean_ = false;
    }

    void Scene::remove_entity(Entity *entity) {
        if (const auto found_entity = std::ranges::find_if(
            entities_,
            [entity](const std::shared_ptr<Entity> &element) {
                return element.get() == entity;
            }
        ); found_entity != entities_.end()) {
            remove_entity(*found_entity);
        }
    }

    void Scene::remove_entities(const std::list<std::shared_ptr<Entity> > &entities) {
        for (const auto &entity: entities) {
            remove_entity(entity);
        }
    }

    void Scene::initialize_() {
        if (initialized_) {
            return;
        }
        Time::restart_();
        initialize();
        initialized_ = true;
    }

    void Scene::update_() {
        update();
        clean_();
        entities_.sort(Entity::sort);
        for (const auto &entity: entities_) {
            entity->update_();
        }
    }

    void Scene::clean_() {
        if (is_clean_) {
            return;
        }
        do {
            is_clean_ = true;
            add_pending_entities_();
            remove_pending_entities_();
            // ReSharper disable once CppDFAConstantConditions
        } while (!is_clean_);
    }

    void Scene::add_pending_entities_() {
        const std::set entities_too_add(entities_to_add_.begin(), entities_to_add_.end());
        for (const auto &entity: entities_too_add) {
            entities_.push_back(entity);
        }
        for (const auto &entity: entities_too_add) {
            entity->start_();
            entities_to_add_.erase(entity);
        }
    }

    void Scene::remove_pending_entities_() {
        const std::set entities_too_remove(entities_to_remove_.begin(), entities_to_remove_.end());
        for (const auto &entity: entities_too_remove) {
            entities_.remove(entity);
        }
        for (const auto &entity: entities_too_remove) {
            entity->destroy_();
            entities_to_remove_.erase(entity);
        }
    }
}
