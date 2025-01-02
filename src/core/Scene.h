#pragma once

namespace inferno {
    class Scene {
    public:
        virtual ~Scene();

    protected:
        virtual void initialize();

        virtual void update();

    private:
        bool initialized_ = false;

        void initialize_();

        void update_();

        friend class Game;
    };
}
