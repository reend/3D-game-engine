#pragma once
#include "raylib-cpp.hpp"
#include "../models/ModelLoader.hpp"

class Renderer {
public:
    static void DrawScene(raylib::Camera3D& camera, ModelLoader& modelLoader);
    static void DrawUI();
}; 