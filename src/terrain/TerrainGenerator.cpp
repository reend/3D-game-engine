#include "TerrainGenerator.hpp"

const float TerrainGenerator::MIN_HEIGHT = -2.0f;
const float TerrainGenerator::MAX_HEIGHT = 2.0f;

TerrainGenerator::TerrainGenerator() {
    GenerateTerrain();
}

void TerrainGenerator::GenerateTerrain() {
    flying += 0.01f;
    
    float yoff = flying;
    for (int x = 0; x < COLS; x++) {
        float xoff = 0.0f;
        for (int y = 0; y < ROWS; y++) {
          
            float height = sin(xoff) * cos(yoff);
            terrain[x][y] = height * (MAX_HEIGHT - MIN_HEIGHT) / 2;
            
            xoff += 0.2f;
        }
        yoff += 0.2f;
    }
}

void TerrainGenerator::Update() {
    GenerateTerrain();
}

void TerrainGenerator::Draw() {
   
    Vector3 offset = {-COLS * CELL_SIZE / 2.0f, -5.0f, -ROWS * CELL_SIZE / 2.0f};  // Y и Z поменяли местами
    
    for (int x = 0; x < COLS - 1; x++) {
        for (int y = 0; y < ROWS - 1; y++) {
            float heightTopLeft = terrain[x][y];
            float heightTopRight = terrain[x + 1][y];
            float heightBottomLeft = terrain[x][y + 1];
            float heightBottomRight = terrain[x + 1][y + 1];

            Vector3 topLeft = {
                offset.x + x * CELL_SIZE,          // X
                offset.y + heightTopLeft,          // Y (height)
                offset.z + y * CELL_SIZE           // Z
            };
            Vector3 topRight = {
                offset.x + (x + 1) * CELL_SIZE,    // X
                offset.y + heightTopRight,         // Y (height)
                offset.z + y * CELL_SIZE           // Z
            };
            Vector3 bottomLeft = {
                offset.x + x * CELL_SIZE,          // X
                offset.y + heightBottomLeft,       // Y (height)
                offset.z + (y + 1) * CELL_SIZE     // Z
            };
            Vector3 bottomRight = {
                offset.x + (x + 1) * CELL_SIZE,    // X
                offset.y + heightBottomRight,      // Y (height)
                offset.z + (y + 1) * CELL_SIZE     // Z
            };

            DrawLine3D(topLeft, topRight, GRAY);
            DrawLine3D(topLeft, bottomLeft, GRAY);
            DrawLine3D(topRight, bottomLeft, GRAY);
            DrawLine3D(topLeft, bottomRight, GRAY);
        }
    }
} 