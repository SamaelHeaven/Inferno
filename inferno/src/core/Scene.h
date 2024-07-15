#pragma once

namespace inferno {
    class Scene {
    public:
        virtual ~Scene();

    protected:
        virtual void initialize();

        virtual void update();

    private:
        bool _initialized = false;

        void _initialize();

        void _update();

        friend class Game;
    };
}
