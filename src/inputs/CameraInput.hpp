#pragma once
#include "raylib-cpp.hpp"

class CameraInput {
public:
    void Update(float deltaTime, float sensitivity);
    float GetPitch() const { return cameraPitch; }
    float GetYaw() const { return cameraYaw; }
    Vector3 GetForwardVector() const;
    
private:
    float cameraPitch = 0.0f;
    float cameraYaw = 0.0f;
    static constexpr float MAX_PITCH = 1.5f;
};