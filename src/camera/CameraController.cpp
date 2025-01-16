#include "CameraController.hpp"

CameraController::CameraController(raylib::Camera3D& camera) : camera(camera) {}

void CameraController::Update() {
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

    if (IsKeyPressed(KEY_R)) Reset();
}

void CameraController::Reset() {
    cameraAngleX = 0.0f;
    cameraAngleY = 0.0f;
    camera.SetPosition(Vector3{50.0f, 50.0f, 50.0f});
    camera.SetTarget(Vector3{0.0f, 0.0f, 0.0f});
} 