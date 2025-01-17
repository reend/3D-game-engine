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
    
    // Обновляем позицию
    raylib::Vector3 newPosition = position;
    
    // Горизонтальное движение (без накопления скорости)
    newPosition.x += velocity.x * deltaTime;
    newPosition.z += velocity.z * deltaTime;
    
    // Вертикальное движение
    if (!isGrounded) {
        newPosition.y += velocity.y * deltaTime;
    }
    
    // Проверяем коллизию с землёй
    if (ground) {
        float groundLevel = ground->GetHeight();
        float playerBottom = newPosition.y - height/2; // Позиция нижней точки игрока
        
        if (playerBottom <= groundLevel) {
            // Устанавливаем игрока точно на землю
            newPosition.y = groundLevel + height/2;
            isGrounded = true;
            velocity.y = 0.0f;
        } else {
            isGrounded = false;
        }
    }
    
    position = newPosition;
    
    // Сбрасываем горизонтальную скорость каждый кадр (предотвращает ускорение)
    velocity.x = 0.0f;
    velocity.z = 0.0f;
}

void PhysicsBody::ApplyForce(const raylib::Vector3& force) {
    // Для ходьбы применяем силу напрямую к скорости, без ускорения
    if (force.y == 0.0f) { // Если это горизонтальное движение
        velocity.x = force.x;
        velocity.z = force.z;
    } else { // Для вертикальных сил (прыжок)
        velocity.y = force.y;
        isGrounded = false; // При прыжке сразу отмечаем, что не на земле
    }
}

void PhysicsBody::SetGrounded(bool grounded) {
    isGrounded = grounded;
} 