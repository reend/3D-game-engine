#pragma once
#include "raylib-cpp.hpp"

class CameraController {
private:
    raylib::Camera3D& camera;
    float cameraAngleX = 0.0f;
    float cameraAngleY = 0.0f;

public:
    CameraController(raylib::Camera3D& camera);
    void Update();
    void Reset();
}; 