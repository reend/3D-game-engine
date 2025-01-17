#include "Player.hpp"
#include "raymath.h"

Player::Player(raylib::Camera3D& cam) : 
    camera(cam),
    physicsBody(cam.position),
    moveSpeed(15.0f),
    jumpForce(15.0f),
    cameraPitch(0.0f),
    cameraYaw(0.0f),
    cameraHeight(4.0f)
{
}

void Player::Update(float deltaTime) {
    HandleInput(deltaTime);
    physicsBody.Update(deltaTime);
    UpdateCamera();
}

void Player::HandleInput(float deltaTime) {
    float mouseSensitivity = 0.002f;
    float mouseX = GetMouseDelta().x * mouseSensitivity;
    float mouseY = GetMouseDelta().y * mouseSensitivity;
    
    cameraYaw -= mouseX; // left-right
    cameraPitch -= mouseY; // up-down
    
    cameraPitch = fmaxf(fminf(cameraPitch, 1.5f), -1.5f);
    
    Vector3 forward;
    forward.x = cosf(cameraPitch) * sinf(cameraYaw);
    forward.y = sinf(cameraPitch);
    forward.z = cosf(cameraPitch) * cosf(cameraYaw);
    forward = Vector3Normalize(forward);
    
    camera.target = Vector3Add(camera.position, forward);
    
    Vector3 moveForward = forward;
    moveForward.y = 0;
    moveForward = Vector3Normalize(moveForward);
    
    Vector3 right = Vector3CrossProduct(moveForward, (Vector3){0, 1, 0});
    right = Vector3Normalize(right);
    
    raylib::Vector3 moveDirection(0.0f, 0.0f, 0.0f);
    
    if (IsKeyDown(KEY_W)) {
        moveDirection.x += moveForward.x;
        moveDirection.z += moveForward.z;
    }
    if (IsKeyDown(KEY_S)) {
        moveDirection.x -= moveForward.x;
        moveDirection.z -= moveForward.z;
    }
    
    if (IsKeyDown(KEY_A)) {
        moveDirection.x -= right.x;
        moveDirection.z -= right.z;
    }
    if (IsKeyDown(KEY_D)) {
        moveDirection.x += right.x;
        moveDirection.z += right.z;
    }
    
    if (IsKeyPressed(KEY_SPACE) && physicsBody.IsGrounded()) {
        physicsBody.ApplyForce(raylib::Vector3(0.0f, jumpForce, 0.0f));
    }
    
    if (moveDirection.Length() > 0) {
        moveDirection = moveDirection.Normalize();
        physicsBody.ApplyForce(moveDirection * moveSpeed);
    }
}

void Player::UpdateCamera() {
    raylib::Vector3 cameraPos = physicsBody.GetPosition();
    cameraPos.y = physicsBody.GetPosition().y + cameraHeight;
    camera.position = cameraPos;
    
    Vector3 forward;
    forward.x = cosf(cameraPitch) * sinf(cameraYaw);
    forward.y = sinf(cameraPitch);
    forward.z = cosf(cameraPitch) * cosf(cameraYaw);
    forward = Vector3Normalize(forward);
    
    camera.target = Vector3Add(camera.position, forward);
} 