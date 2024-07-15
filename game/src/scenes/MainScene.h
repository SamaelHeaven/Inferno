#pragma once

#include "../game.h"

class MainScene final : public Scene {
public:
    MainScene();

    ~MainScene() override;

protected:
    void initialize() override;

    void update() override;
};
