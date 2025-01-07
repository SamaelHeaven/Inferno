#pragma once

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

        static void system(const System &system);

        void on_update(const UpdateListener &update_listener);

        void on_ordered_update(const OrderedUpdateListener &update_listener);

        void on_fixed_update(const FixedUpdateListener &fixed_update_listener);

        template <typename... T, typename Callback>
        std::enable_if_t<std::is_invocable_v<Callback, Entity, T &...>> on_add(Callback &&callback) {
            const auto candidate = [&](entt::entity entity, entt::registry &, auto &...components) {
                callback(static_cast<Entity>(entity), components...);
            };
            registry_.on_construct<T...>().template connect<candidate>();
        }

        template <typename... T> void on_remove(const std::function<void(Entity)> &callback) {
            const auto candidate = [&](entt::entity entity) {
                callback(static_cast<Entity>(entity));
            };
            registry_.on_destroy<T...>().template connect<candidate>();
        }

        Entity create();

        void destroy(Entity entity);

        template <typename T, typename... Args, std::enable_if_t<std::is_constructible_v<T, Args...>> * = nullptr>
        T &add(Entity entity, Args &&...args) {
            return registry_.emplace<T>(static_cast<entt::entity>(entity), std::forward<Args>(args)...);
        }

        template <typename T> [[nodiscard]] T *get(Entity entity) {
            return registry_.try_get<T>(static_cast<entt::entity>(entity));
        }

        template <typename T, typename... Other> std::size_t remove(Entity entity) {
            return registry_.remove<T, Other...>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool all_of(Entity entity) const {
            return registry_.all_of<T...>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool any_of(Entity entity) const {
            return registry_.any_of<T...>(static_cast<entt::entity>(entity));
        }

        template <typename... T, typename Callback>
        std::enable_if_t<std::is_invocable_v<Callback, Entity, T &...> || std::is_invocable_v<Callback, T &...>> each(
            Callback &&callback) {
            auto view = registry_.view<T...>();
            view.each([&](entt::entity entity, auto &...components) {
                if constexpr (std::is_invocable_v<Callback, Entity, T &...>) {
                    callback(static_cast<Entity>(entity), components...);
                } else if constexpr (std::is_invocable_v<Callback, T &...>) {
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
