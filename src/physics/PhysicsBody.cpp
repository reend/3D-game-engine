#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody(const raylib::Vector3& pos, float mass) : 
    position(pos),
    mass(mass),
    isGrounded(false),
    height(4.0f),
    ground(nullptr)
{
    velocity = raylib::Vector3(0.0f, 0.0f, 0.0f);
    acceleration = raylib::Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsBody::Update(float deltaTime) {
    if (!isGrounded) {
        velocity.y += GRAVITY * deltaTime;
    }
    
    raylib::Vector3 newPosition = position;
    
    newPosition.x += velocity.x * deltaTime;
    newPosition.z += velocity.z * deltaTime;
    
    if (!isGrounded) {
        newPosition.y += velocity.y * deltaTime;
    }
    
    if (ground) {
        float groundLevel = ground->GetHeight();
        float playerBottom = newPosition.y - height/2; 
        
        if (playerBottom <= groundLevel) {
            newPosition.y = groundLevel + height/2;
            isGrounded = true;
            velocity.y = 0.0f;
        } else {
            isGrounded = false;
        }
    }
    
    position = newPosition;
    
    velocity.x = 0.0f;
    velocity.z = 0.0f;
}

void PhysicsBody::ApplyForce(const raylib::Vector3& force) {
    if (force.y == 0.0f) { 
        velocity.x = force.x;
        velocity.z = force.z;
    } else {
        velocity.y = force.y;
        isGrounded = false; 
    }
}

void PhysicsBody::SetGrounded(bool grounded) {
    isGrounded = grounded;
} 