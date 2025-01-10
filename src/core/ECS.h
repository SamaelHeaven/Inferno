#pragma once

#include "../components/Transform.h"
#include "../inferno.h"

namespace inferno {
    enum class Entity : uint32_t {};

    using System = std::function<void(class ECS &)>;

    using UpdateListener = std::function<void()>;

    using OrderedUpdateListener = std::function<void(Entity)>;

    using FixedUpdateListener = std::function<void()>;

    class ECS final {
    public:
        ECS(const ECS &) = delete;

        ~ECS();

        static ECS &current();

        static void system(const System &system);

        void on_update(const UpdateListener &update_listener);

        void on_ordered_update(const OrderedUpdateListener &update_listener);

        void on_fixed_update(const FixedUpdateListener &fixed_update_listener);

    private:
        static std::unordered_map<const entt::registry *, ECS *> ecs_map_;

    public:
        template <typename Component, auto Callback,
            auto Candidate =
                [](const entt::registry &registry, entt::entity entity) {
                    Callback(*ecs_map_.find(&registry)->second, static_cast<Entity>(entity));
                }>
        std::enable_if_t<std::is_invocable_v<decltype(Callback), ECS &, Entity>> on_add() {
            registry_.on_construct<Component>().template connect<Candidate>();
        }

        template <typename Component, auto Callback,
            auto Candidate =
                [](const entt::registry &registry, entt::entity entity) {
                    Callback(*ecs_map_.find(&registry)->second, static_cast<Entity>(entity));
                }>
        std::enable_if_t<std::is_invocable_v<decltype(Callback), ECS &, Entity>> on_remove() {
            registry_.on_destroy<Component>().template connect<Candidate>();
        }

        Entity create();

        void destroy(Entity entity);

        template <typename Component, typename... Args,
            std::enable_if_t<!std::is_same_v<Component, Transform> && std::is_constructible_v<Component, Args...>,
                int32_t> = 0>
        Component &add(Entity entity, Args &&...args) {
            return registry_.emplace<Component>(static_cast<entt::entity>(entity), std::forward<Args>(args)...);
        }

        template <typename Component> [[nodiscard]] Component *get(Entity entity) {
            return registry_.try_get<Component>(static_cast<entt::entity>(entity));
        }

        template <typename Component, typename... Other,
            std::enable_if_t<!std::is_same_v<Component, Transform>, int32_t> = 0>
        std::size_t remove(Entity entity) {
            return registry_.remove<Component, Other...>(static_cast<entt::entity>(entity));
        }

        template <typename... Component> [[nodiscard]] bool all_of(Entity entity) const {
            return registry_.all_of<Component...>(static_cast<entt::entity>(entity));
        }

        template <typename... Component> [[nodiscard]] bool any_of(Entity entity) const {
            return registry_.any_of<Component...>(static_cast<entt::entity>(entity));
        }

        template <typename... Component, typename Callback>
        std::enable_if_t<std::is_invocable_v<Callback, Entity, Component &...> ||
            std::is_invocable_v<Callback, Component &...>>
        each(Callback &&callback) {
            auto view = registry_.view<Component...>();
            view.each([&](entt::entity entity, auto &...components) {
                if constexpr (std::is_invocable_v<Callback, Entity, Component &...>) {
                    callback(static_cast<Entity>(entity), components...);
                } else if constexpr (std::is_invocable_v<Callback, Component &...>) {
                    callback(components...);
                } else {
                    static_assert(false, "Invalid callback signature");
                }
            });
        }

    private:
        static std::vector<System> systems_;

        std::vector<UpdateListener> update_listeners_;

        std::vector<OrderedUpdateListener> ordered_update_listeners_;

        std::vector<FixedUpdateListener> fixed_update_listeners_;

        entt::registry registry_;

        std::vector<std::pair<const int32_t *, Entity>> entities_;

        std::vector<Entity> entities_to_create_;

        std::vector<Entity> entities_to_destroy_;

        ECS();

        friend class Scene;
    };
}
