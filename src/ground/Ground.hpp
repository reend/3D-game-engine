#pragma once
#include "raylib-cpp.hpp"

class Ground {
private:
    Model model;
    raylib::Texture2D texture;
    float width;
    float length;
    Vector3 position;

public:
    Ground();
    ~Ground();
    void Init();
    void Draw();
}; 