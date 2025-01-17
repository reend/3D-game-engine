#include "Player.hpp"
#include "raymath.h"

Player::Player(raylib::Camera3D& cam, InputManager& input) : 
    camera(cam),
    inputManager(input),
    physicsBody(cam.position),
    moveSpeed(15.0f),
    jumpForce(15.0f),
    cameraPitch(0.0f),
    cameraYaw(0.0f),
    cameraHeight(4.0f)
{
}

void Player::Update(float deltaTime) {
    auto inputState = inputManager.Update(deltaTime, 0.002f);
    
    cameraPitch = inputState.cameraPitch;
    cameraYaw = inputState.cameraYaw;
    
    if (inputState.jumpRequested && physicsBody.IsGrounded()) {
        physicsBody.ApplyForce(raylib::Vector3(0.0f, jumpForce, 0.0f));
    }
    
    if (inputState.moveDirection.Length() > 0) {
        physicsBody.ApplyForce(inputState.moveDirection * moveSpeed);
    }
    
    physicsBody.Update(deltaTime);
    UpdateCamera();
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