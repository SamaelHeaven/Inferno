#pragma once

#include "../components/Transform.h"
#include "../inferno.h"

namespace inferno {
    enum class Entity : uint32_t {};

    using System = std::function<void(class ECS &)>;

    using UpdateListener = std::function<void()>;

    using FixedUpdateListener = std::function<void()>;

    class ECS final {
    public:
        ECS(const ECS &) = delete;

        static void system(const System &system);

        void on_update(const UpdateListener &update_listener);

        void on_fixed_update(const FixedUpdateListener &fixed_update_listener);

        template <typename... T> void on_add(const std::function<void(Entity)> &callback) {
            registry_.on_construct<T...>().connect([&](entt::entity entity) {
                callback(static_cast<Entity>(entity));
            });
        }

        template <typename... T> void on_remove(const std::function<void(Entity)> &callback) {
            registry_.on_destroy<T...>().connect([&](entt::entity entity) {
                callback(static_cast<Entity>(entity));
            });
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

        template <typename... T> [[nodiscard]] bool has_all_of(Entity entity) const {
            return registry_.all_of<T...>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool has_any_of(Entity entity) const {
            return registry_.any_of<T...>(static_cast<entt::entity>(entity));
        }

        template <typename... T, typename Callback>
        std::enable_if_t<std::is_invocable_v<Callback, Entity, T &...> || std::is_invocable_v<Callback, T &...>>
        for_each(Callback &&callback) {
            auto view = registry_.view<T...>();
            view.sort([&](const entt::entity lhs, const entt::entity rhs) {
                const auto &lhs_transform = registry_.get<Transform>(lhs);
                const auto &rhs_transform = registry_.get<Transform>(rhs);
                return lhs_transform.get_z_index() < rhs_transform.get_z_index();
            });
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

        std::vector<FixedUpdateListener> fixed_update_listeners_;

        ECS();

        entt::registry registry_;

        friend class Scene;
    };
}
