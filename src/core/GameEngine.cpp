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
        
        // Update other systems
        modelLoader.Update();
        
        // Render scene
        Renderer::DrawScene(camera, modelLoader, terrain, ground);
    }
} 