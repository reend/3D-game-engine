#pragma once
#include "raylib-cpp.hpp"
#include "../models/ModelLoader.hpp"
#include "../terrain/TerrainGenerator.hpp"
#include "../ground/Ground.hpp"

class Renderer {
public:
    static void DrawScene(raylib::Camera3D& camera, ModelLoader& modelLoader, TerrainGenerator& terrain, Ground& ground);
    static void DrawUI();
}; 