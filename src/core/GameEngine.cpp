#include "GameEngine.hpp"

GameEngine::GameEngine() : 
    window(1280, 720, "3D"),
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
    player = std::make_unique<Player>(camera);
}

void GameEngine::Load() {
    modelLoader.LoadFromFile("resources/models/cube.obj");
    ground.Init();
    player->GetPhysicsBody().SetGround(&ground);
}

void GameEngine::Run() {
    while (!window.ShouldClose()) {
        deltaTime = GetFrameTime();
        
        // Update player physics and movement
        player->Update(deltaTime);
        
        modelLoader.Update();
        
        Renderer::DrawScene(camera, modelLoader, terrain, ground);
    }
} 