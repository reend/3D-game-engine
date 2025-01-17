#pragma once
#include "../physics/PhysicsBody.hpp"
#include "raylib-cpp.hpp"
#include "../inputs/InputManager.hpp"

// Forward declaration if needed
class PhysicsBody;

class Player {
private:
    PhysicsBody physicsBody;
    raylib::Camera3D& camera;
    InputManager& inputManager;
    float moveSpeed;
    float jumpForce;
    float cameraPitch; 
    float cameraYaw;
    float cameraHeight;
    
public:
    Player(raylib::Camera3D& camera, InputManager& inputManager);
    
    void Update(float deltaTime);
    void UpdateCamera();
    
    const raylib::Vector3& GetPosition() const { return physicsBody.GetPosition(); }
    PhysicsBody& GetPhysicsBody() { return physicsBody; }
}; 