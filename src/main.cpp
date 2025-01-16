#include "raylib-cpp.hpp"

class GameEngine {
private:
    raylib::Window window;
    raylib::Camera3D camera;
    raylib::Model model;
    raylib::Vector3 modelPosition;

public:
    GameEngine() : 
        window(800, 600, "3D Game Engine"),
        camera(
            raylib::Vector3(20.0f, 20.0f, 20.0f),  // Увеличили дистанцию камеры
            raylib::Vector3(0.0f, 0.0f, 0.0f),     // target
            raylib::Vector3(0.0f, 1.0f, 0.0f),     // up
            45.0f,                                  // FOV
            CAMERA_PERSPECTIVE                      // projection
        ),
        modelPosition(0.0f, 0.0f, 0.0f)
    {
        SetTargetFPS(60);
    }

    void Load() {
        try {
            if (!FileExists("resources/models/cube.obj")) {
                TraceLog(LOG_ERROR, "Model file not found: resources/models/cube.obj");
                return;
            }
            
            model = LoadModel("resources/models/cube.obj");
            
            if (model.meshCount <= 0) {
                TraceLog(LOG_ERROR, "Failed to load model meshes");
                return;
            }
        } catch (const std::exception& e) {
            TraceLog(LOG_ERROR, "Failed to load model: %s", e.what());
        }
    }

    void Run() {
        while (!window.ShouldClose()) {
            Update();
            Draw();
        }
    }

private:
    void Update() {
        // Обновление камеры
        camera.Update(GetFrameTime());
        
        // Простое вращение модели
        modelPosition.y += 1.0f * GetFrameTime();
    }

    void Draw() {
        BeginDrawing();
        {
            window.ClearBackground(RAYWHITE);

            camera.BeginMode();
            {
                DrawGrid(10, 1.0f);
                
                // Уменьшили масштаб модели до 0.2
                model.Draw(modelPosition, 0.2f, WHITE);
                
                DrawLine3D({0,0,0}, {5,0,0}, RED);    // X
                DrawLine3D({0,0,0}, {0,5,0}, GREEN);  // Y
                DrawLine3D({0,0,0}, {0,0,5}, BLUE);   // Z
            }
            camera.EndMode();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }
};

int main() {
    GameEngine engine;
    engine.Load();
    engine.Run();
    return 0;
}