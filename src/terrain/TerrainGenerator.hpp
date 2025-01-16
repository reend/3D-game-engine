#pragma once
#include "raylib-cpp.hpp"

class TerrainGenerator {
private:
    static const int COLS = 100;
    static const int ROWS = 100;
    static const int CELL_SIZE = 1;
    static const float MIN_HEIGHT;
    static const float MAX_HEIGHT;
    
    float terrain[COLS][ROWS];
    float flying = 0.0f;

public:
    TerrainGenerator();
    void Update();
    void Draw();
    void GenerateTerrain();
}; 