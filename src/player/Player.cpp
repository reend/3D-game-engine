#include "Player.hpp"

Player::Player(raylib::Camera3D& cam) : 
    camera(cam),
    physicsBody(cam.position),
    moveSpeed(10.0f),
    jumpForce(5.0f)
{
}

void Player::Update(float deltaTime) {
    HandleInput(deltaTime);
    physicsBody.Update(deltaTime);
    UpdateCamera();
}

void Player::HandleInput(float deltaTime) {
    raylib::Vector3 moveDirection(0.0f, 0.0f, 0.0f);
    
    // Forward/Backward
    if (IsKeyDown(KEY_W)) moveDirection.z -= 1.0f;
    if (IsKeyDown(KEY_S)) moveDirection.z += 1.0f;
    
    // Left/Right
    if (IsKeyDown(KEY_A)) moveDirection.x -= 1.0f;
    if (IsKeyDown(KEY_D)) moveDirection.x += 1.0f;
    
    // Jump
    if (IsKeyPressed(KEY_SPACE) && physicsBody.IsGrounded()) {
        physicsBody.ApplyForce(raylib::Vector3(0.0f, jumpForce, 0.0f));
        physicsBody.SetGrounded(false);
    }
    
    // Normalize and apply movement
    if (moveDirection.Length() > 0) {
        moveDirection = moveDirection.Normalize();
        physicsBody.ApplyForce(moveDirection * moveSpeed);
    }
}

void Player::UpdateCamera() {
    camera.position = physicsBody.GetPosition();
    // Convert raylib::Vector3 to Vector3 for the addition operation
    Vector3 forward = { 0.0f, 0.0f, -1.0f };
    camera.target = Vector3Add(camera.position, forward);
} 