#include "CameraInput.hpp"

void CameraInput::Update(float deltaTime, float sensitivity) {
    float mouseX = GetMouseDelta().x * sensitivity;
    float mouseY = GetMouseDelta().y * sensitivity;
    
    cameraYaw -= mouseX;
    cameraPitch -= mouseY;
    cameraPitch = fmaxf(fminf(cameraPitch, MAX_PITCH), -MAX_PITCH);
}

Vector3 CameraInput::GetForwardVector() const {
    Vector3 forward;
    forward.x = cosf(cameraPitch) * sinf(cameraYaw);
    forward.y = sinf(cameraPitch);
    forward.z = cosf(cameraPitch) * cosf(cameraYaw);
    return Vector3Normalize(forward);
}