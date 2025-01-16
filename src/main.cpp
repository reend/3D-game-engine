#include "raylib-cpp.hpp"

class GameEngine {
private:
    raylib::Window window;
    raylib::Camera3D camera;
    raylib::Model model;
    raylib::Vector3 modelPosition;
    float cameraAngleX = 0.0f;
    float cameraAngleY = 0.0f;

public:
    GameEngine() : 
        window(800, 600, "3D Game Engine"),
        camera(
            raylib::Vector3(50.0f, 50.0f, 50.0f),  // position
            raylib::Vector3(0.0f, 0.0f, 0.0f),     // target
            raylib::Vector3(0.0f, 1.0f, 0.0f),     // up
            45.0f,                                  // FOV
            CAMERA_PERSPECTIVE                      // projection
        ),
        modelPosition(0.0f, 0.0f, 0.0f)
    {
        SetTargetFPS(60);
        DisableCursor();
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

            // debug
            TraceLog(LOG_INFO, "Model loaded successfully:");
            TraceLog(LOG_INFO, "Meshes: %d", model.meshCount);
            TraceLog(LOG_INFO, "Materials: %d", model.materialCount);
            TraceLog(LOG_INFO, "Bones: %d", model.boneCount);
            
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
        Vector2 mouseDelta = GetMouseDelta();
        float sensitivity = 0.003f;
        
        cameraAngleX += mouseDelta.x * sensitivity;
        cameraAngleY += mouseDelta.y * sensitivity;
        
        cameraAngleY = Clamp(cameraAngleY, -1.5f, 1.5f);

        Vector3 forward = {
            cos(cameraAngleX) * cos(cameraAngleY),
            sin(cameraAngleY),
            sin(cameraAngleX) * cos(cameraAngleY)
        };

        float moveSpeed = 0.5f;
        Vector3 position = camera.GetPosition();
        Vector3 right = Vector3CrossProduct(forward, {0, 1, 0});

        if (IsKeyDown(KEY_W)) position = Vector3Add(position, Vector3Scale(forward, moveSpeed));
        if (IsKeyDown(KEY_S)) position = Vector3Subtract(position, Vector3Scale(forward, moveSpeed));
        if (IsKeyDown(KEY_D)) position = Vector3Add(position, Vector3Scale(right, moveSpeed));
        if (IsKeyDown(KEY_A)) position = Vector3Subtract(position, Vector3Scale(right, moveSpeed));

        camera.SetPosition(position);
        camera.SetTarget(Vector3Add(position, forward));

        if (IsKeyPressed(KEY_R)) {
            cameraAngleX = 0.0f;
            cameraAngleY = 0.0f;
            camera.SetPosition(Vector3{50.0f, 50.0f, 50.0f});
        }

        modelPosition.y += 1.0f * GetFrameTime();
    }

    void Draw() {
        BeginDrawing();
        {
            window.ClearBackground(BLACK);

            camera.BeginMode();
            {
                DrawGrid(20, 1.0f);
                
                model.Draw(modelPosition, 1.0f, RED);
                
                DrawLine3D({0,0,0}, {20,0,0}, RED);     // X
                DrawLine3D({0,0,0}, {0,20,0}, GREEN);   // Y
                DrawLine3D({0,0,0}, {0,0,20}, BLUE);    // Z
            }
            camera.EndMode();

            DrawFPS(10, 10);
            DrawText("WASD - move, Mouse - look around", 10, 30, 20, LIGHTGRAY);
            DrawText("Press R to reset camera", 10, 50, 20, LIGHTGRAY);
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