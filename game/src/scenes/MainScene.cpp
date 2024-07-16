#include "./MainScene.h"

MainScene::MainScene() = default;

MainScene::~MainScene() = default;

void MainScene::initialize() {
    std::cout << "Initializing..." << std::endl;
}

void MainScene::update() {
    std::cout << "FPS: " << Time::current_fps() << std::endl;
    Renderer::clear_background(Color::BLUE);
}
