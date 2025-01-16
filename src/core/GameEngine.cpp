#include "GameEngine.hpp"

GameEngine::GameEngine() : 
    window(800, 600, "3D Game Engine"),
    camera(
        raylib::Vector3(50.0f, 50.0f, 50.0f),
        raylib::Vector3(0.0f, 0.0f, 0.0f),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        45.0f,
        CAMERA_PERSPECTIVE
    ),
    cameraController(camera)
{
    SetTargetFPS(60);
    DisableCursor();
}

void GameEngine::Load() {
    modelLoader.LoadFromFile("resources/models/cube.obj");
}

void GameEngine::Run() {
    while (!window.ShouldClose()) {
        cameraController.Update();
        modelLoader.Update();
        Renderer::DrawScene(camera, modelLoader);
    }
} 