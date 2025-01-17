#include "MovementInput.hpp"

raylib::Vector3 MovementInput::GetMovementDirection(const Vector3& forward) const {
    Vector3 moveForward = forward;
    moveForward.y = 0;
    moveForward = Vector3Normalize(moveForward);
    
    Vector3 right = Vector3CrossProduct(moveForward, (Vector3){0, 1, 0});
    right = Vector3Normalize(right);
    
    return CalculateMovementVector(moveForward, right);
}

Vector3 MovementInput::CalculateMovementVector(const Vector3& forward, const Vector3& right) const {
    raylib::Vector3 moveDirection(0.0f, 0.0f, 0.0f);
    
    if (IsKeyDown(KEY_W)) {
        moveDirection.x += forward.x;
        moveDirection.z += forward.z;
    }
    if (IsKeyDown(KEY_S)) {
        moveDirection.x -= forward.x;
        moveDirection.z -= forward.z;
    }
    if (IsKeyDown(KEY_A)) {
        moveDirection.x -= right.x;
        moveDirection.z -= right.z;
    }
    if (IsKeyDown(KEY_D)) {
        moveDirection.x += right.x;
        moveDirection.z += right.z;
    }
    
    return moveDirection.Length() > 0 ? moveDirection.Normalize() : moveDirection;
}

bool MovementInput::IsJumpRequested() const {
    return IsKeyPressed(KEY_SPACE);
}