#pragma once
#include "raylib-cpp.hpp"
#include "../camera/CameraController.hpp"
#include "../models/ModelLoader.hpp"
#include "../rendering/Renderer.hpp"
#include "../terrain/TerrainGenerator.hpp"

class GameEngine {
private:
    raylib::Window window;
    raylib::Camera3D camera;
    CameraController cameraController;
    ModelLoader modelLoader;
    TerrainGenerator terrain;

public:
    GameEngine();
    void Load();
    void Run();
}; 