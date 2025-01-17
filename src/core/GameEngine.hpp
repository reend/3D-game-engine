#pragma once
#include <memory>
#include "raylib-cpp.hpp"
#include "../camera/CameraController.hpp"
#include "../player/Player.hpp"
#include "../models/ModelLoader.hpp"
#include "../rendering/Renderer.hpp"
#include "../terrain/TerrainGenerator.hpp"
#include "../ground/Ground.hpp"
#include "../inputs/InputManager.hpp"

class GameEngine {
private:
    raylib::Window window;
    raylib::Camera3D camera;
    std::unique_ptr<Player> player;
    InputManager inputManager;
    float deltaTime;
    Ground ground;
    ModelLoader modelLoader;
    
public:
    GameEngine();
    void Load();
    void Run();
}; 