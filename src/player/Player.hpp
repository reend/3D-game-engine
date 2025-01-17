#pragma once
#include "../physics/PhysicsBody.hpp"
#include "raylib-cpp.hpp"

// Forward declaration if needed
class PhysicsBody;

class Player {
private:
    PhysicsBody physicsBody;
    raylib::Camera3D& camera;
    float moveSpeed;
    float jumpForce;
    float cameraPitch;  // Угол наклона камеры (вверх/вниз)
    float cameraYaw;    // Угол поворота камеры (влево/вправо)
    float cameraHeight;  // Добавляем фиксированную высоту камеры
    
public:
    explicit Player(raylib::Camera3D& camera);
    
    void Update(float deltaTime);
    void HandleInput(float deltaTime);
    void UpdateCamera();
    
    const raylib::Vector3& GetPosition() const { return physicsBody.GetPosition(); }
    PhysicsBody& GetPhysicsBody() { return physicsBody; }
}; 