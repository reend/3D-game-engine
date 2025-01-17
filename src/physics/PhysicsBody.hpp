#pragma once
#include "raylib-cpp.hpp"
#include "../ground/Ground.hpp"

class PhysicsBody {
private:
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;
    float mass;
    bool isGrounded;
    float height;
    const Ground* ground;
    
public:
    static constexpr float GRAVITY = -25.0f;
    
    PhysicsBody(const raylib::Vector3& pos, float mass = 1.0f);
    
    void Update(float deltaTime);
    void ApplyForce(const raylib::Vector3& force);
    void SetGrounded(bool grounded);
    void SetGround(const Ground* g) { ground = g; }
    
    bool IsGrounded() const { return isGrounded; }
    const raylib::Vector3& GetPosition() const { return position; }
    void SetPosition(const raylib::Vector3& pos) { position = pos; }
    float GetHeight() const { return height; }
}; 