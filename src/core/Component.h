#pragma once

namespace inferno {
    class Entity;

    class Component {
    public:
        virtual ~Component() = default;

        [[nodiscard]] Entity *get_entity() const;

    protected:
        virtual void start() {}

        virtual void update() {}

        virtual void fixed_update() {}

        virtual void destroy() {}

    private:
        Entity *entity_ = nullptr;

        friend class Entity;
    };
}
