#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody(const raylib::Vector3& pos, float mass) : 
    position(pos),
    mass(mass),
    isGrounded(false),
    height(2.0f), // Высота игрока
    ground(nullptr)
{
    velocity = raylib::Vector3(0.0f, 0.0f, 0.0f);
    acceleration = raylib::Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsBody::SetGrounded(bool grounded) {
    isGrounded = grounded;
}

void PhysicsBody::Update(float deltaTime) {
    if (!isGrounded) {
        // Применяем гравитацию
        acceleration.y = GRAVITY;
    } else {
        acceleration.y = 0.0f;
        velocity.y = 0.0f;
    }
    
    // Обновляем скорость
    velocity += acceleration * deltaTime;
    
    // Обновляем позицию
    raylib::Vector3 newPosition = position + velocity * deltaTime;
    
    // Проверяем коллизию с землёй
    if (ground) {
        Vector3 checkPoint = { newPosition.x, newPosition.y, newPosition.z };
        if (ground->CheckCollision(checkPoint)) {
            // При коллизии устанавливаем позицию на уровне земли
            newPosition.y = ground->GetHeight() + height/2;
            isGrounded = true;
            velocity.y = 0.0f;
        } else {
            isGrounded = false;
        }
    }
    
    position = newPosition;
    
    // Сбрасываем ускорение
    acceleration = raylib::Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsBody::ApplyForce(const raylib::Vector3& force) {
    acceleration += force / mass;
} 