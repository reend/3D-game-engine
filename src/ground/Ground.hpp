#pragma once
#include "raylib-cpp.hpp"

class Ground {
private:
    Model model;
    raylib::Texture2D texture;
    float width;
    float length;
    Vector3 position;
    float height;  // Высота земли

public:
    Ground();
    ~Ground();
    void Init();
    void Draw();
    
    // Методы для коллизий
    float GetHeight() const { return height; }
    bool CheckCollision(const Vector3& point) const;
    Vector3 GetDimensions() const { return {width, height, length}; }
    Vector3 GetPosition() const { return position; }
}; 