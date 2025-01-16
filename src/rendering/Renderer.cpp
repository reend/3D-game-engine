#include "Renderer.hpp"

void Renderer::DrawScene(raylib::Camera3D& camera, ModelLoader& modelLoader) {
    BeginDrawing();
    {
        ClearBackground(BLACK);

        camera.BeginMode();
        {
            DrawGrid(20, 1.0f);
            modelLoader.Draw();
            
            DrawLine3D({0,0,0}, {20,0,0}, RED);    // X
            DrawLine3D({0,0,0}, {0,20,0}, GREEN);  // Y
            DrawLine3D({0,0,0}, {0,0,20}, BLUE);   // Z
        }
        camera.EndMode();

        DrawUI();
    }
    EndDrawing();
}

void Renderer::DrawUI() {
    DrawFPS(10, 10);
    DrawText("WASD - move, Mouse - look around", 10, 30, 20, LIGHTGRAY);
    DrawText("Press R to reset camera", 10, 50, 20, LIGHTGRAY);
} 