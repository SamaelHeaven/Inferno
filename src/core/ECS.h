#pragma once

#include "../drawing/Color.h"
#include "../inferno.h"

namespace inferno {
    using System = std::function<void(class ECS &)>;

    enum class Entity : uint32_t {};

    class ECS final {
    public:
        ECS(const ECS &) = delete;

        static void system(const System &system);

        Entity create();

        void destroy(Entity entity);

        template <typename T, typename... Args, std::enable_if_t<std::is_constructible_v<T, Args...>> * = nullptr>
        auto add(Entity entity, Args... args) {
            return registry_.emplace<T>(entity, args...);
        }

        template <typename T, typename... O> std::size_t remove(Entity entity) {
            return registry_.remove<T, O>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool hasAllOf(Entity entity) const {
            return registry_.all_of<T>(static_cast<entt::entity>(entity));
        }

        template <typename... T> [[nodiscard]] bool hasAnyOf(Entity entity) const {
            return registry_.any_of<T>(static_cast<entt::entity>(entity));
        }

        template <typename... T> void forEach(const std::function<void(Entity, T &...)> &callback) {
            auto view = registry_.view<T...>();
            view.each(callback);
        }

    private:
        static std::vector<System> systems_;

        ECS();

        entt::registry registry_;

        friend class Scene;
    };
}
