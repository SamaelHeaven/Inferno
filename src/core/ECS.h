#pragma once

#include "../drawing/Color.h"
#include "../inferno.h"

namespace inferno {
    typedef void (*System)(class ECS &);

    enum class Entity : uint32_t {};

    class ECS final {
    public:
        ECS(const ECS &) = delete;

        static void system(const System &system);

        Entity create();

        void destroy(Entity entity);

        template <typename T, typename... Args, std::enable_if_t<std::is_constructible_v<T, Args...>> * = nullptr>
        auto add(Entity entity, Args &&...args) {
            return registry_.emplace<T>(static_cast<entt::entity>(entity), std::forward<Args>(args)...);
        }

        template <typename T, typename... Other> std::size_t remove(Entity entity) {
            return registry_.remove<T, Other...>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool hasAllOf(Entity entity) const {
            return registry_.all_of<T...>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool hasAnyOf(Entity entity) const {
            return registry_.any_of<T...>(static_cast<entt::entity>(entity));
        }

        template <typename... T, std::invocable Callback> void forEach(Callback callback) {
            registry_.view<T...>().each([callback]<typename... Components>(auto entity, Components &...components) {
                if constexpr (std::is_invocable_v<Callback, Entity, Components...>()) {
                    callback(static_cast<Entity>(entity), components...);
                } else {
                    callback(components...);
                }
            });
        }

    private:
        static std::vector<System> systems_;

        ECS();

        entt::registry registry_;

        friend class Scene;
    };
}
