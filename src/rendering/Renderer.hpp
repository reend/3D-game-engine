#pragma once
#include "raylib-cpp.hpp"
#include "../models/ModelLoader.hpp"
#include "../terrain/TerrainGenerator.hpp"

class Renderer {
public:
    static void DrawScene(raylib::Camera3D& camera, ModelLoader& modelLoader, TerrainGenerator& terrain);
    static void DrawUI();
}; 