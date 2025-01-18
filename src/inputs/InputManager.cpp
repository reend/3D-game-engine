#include "InputManager.hpp"

CameraInput InputManager::cameraInput;
MovementInput InputManager::movementInput;

InputState InputManager::Update(float deltaTime, float mouseSensitivity) {
    InputState state;
    
    cameraInput.Update(deltaTime, mouseSensitivity);
    state.cameraPitch = cameraInput.GetPitch();
    state.cameraYaw = cameraInput.GetYaw();
    
    Vector3 forward = cameraInput.GetForwardVector();
    state.moveDirection = movementInput.GetMovementDirection(forward);
    
    state.jumpRequested = movementInput.IsJumpRequested();
    
    return state;
}

void InputManager::Init() {
}
