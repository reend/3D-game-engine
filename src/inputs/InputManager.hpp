#pragma once
#include "raylib-cpp.hpp"
#include "CameraInput.hpp"
#include "MovementInput.hpp"

struct InputState {
    raylib::Vector3 moveDirection;
    float cameraPitch;
    float cameraYaw;
    bool jumpRequested;
};

class InputManager {
public:
    static InputState Update(float deltaTime, float mouseSensitivity);
    static void Init();
    
private:
    static CameraInput cameraInput;
    static MovementInput movementInput;
};