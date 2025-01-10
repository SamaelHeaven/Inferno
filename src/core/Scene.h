#pragma once

#include "./ECS.h"

namespace inferno {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene();

        static std::shared_ptr<Scene> current();

        ECS &get_ecs();

        virtual void initialize();

        virtual void fixed_update();

        virtual void update();

    private:
        float time_ = 0.0f;

        ECS ecs_;

        bool initialized_ = false;

        void initialize_();

        void fixed_update_();

        void update_();

        friend class Game;
    };
}
