#pragma once
#include <memory>
#include "raylib-cpp.hpp"
#include "../camera/CameraController.hpp"
#include "../player/Player.hpp"
#include "../models/ModelLoader.hpp"
#include "../rendering/Renderer.hpp"
#include "../terrain/TerrainGenerator.hpp"
#include "../ground/Ground.hpp"

class GameEngine {
private:
    raylib::Window window;
    raylib::Camera3D camera;
    std::unique_ptr<Player> player;
    CameraController cameraController;
    ModelLoader modelLoader;
    TerrainGenerator terrain;
    Ground ground;
    float deltaTime;

public:
    GameEngine();
    void Load();
    void Run();
}; 