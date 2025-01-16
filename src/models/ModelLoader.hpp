#pragma once
#include "raylib-cpp.hpp"
#include <string>

class ModelLoader {
private:
    raylib::Model model;
    raylib::Vector3 position;

public:
    ModelLoader();
    bool LoadFromFile(const std::string& path);
    void Update();
    void Draw();
    
    const raylib::Model& GetModel() const { return model; }
    const raylib::Vector3& GetPosition() const { return position; }
}; 