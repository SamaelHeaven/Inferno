#pragma once

#include "./ECS.h"

namespace inferno {
    class Scene {
    public:
        virtual ~Scene();

        ECS &get_ecs();

    protected:
        virtual void initialize();

        virtual void update();

    private:
        ECS ecs_;

        bool initialized_ = false;

        void initialize_();

        void update_();

        friend class Game;
    };
}
