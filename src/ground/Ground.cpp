#include "Ground.hpp"
#include "rlgl.h"

Ground::Ground() {
    width = 20.0f;  
    length = 20.0f;
    height = 0.0f;  // Уровень земли
    
    position = {
        0.0f,  
        height,  
        0.0f   
    };
}

Ground::~Ground() {
    if (texture.id > 0) {
        UnloadTexture(texture);
    }
    UnloadModel(model);
}

void Ground::Init() {
    texture = LoadTexture("resources/textures/lava.png");
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture!");
    } else {
        TraceLog(LOG_INFO, "Texture loaded successfully: %d", texture.id);
    }
    
    SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
    
    Mesh mesh = GenMeshPlane(width, length, 20, 20);
    
    for (int i = 0; i < mesh.vertexCount; i++) {
        int texcoordIndex = i * 2;
        float u = mesh.texcoords[texcoordIndex];
        float v = mesh.texcoords[texcoordIndex + 1];
        
        mesh.texcoords[texcoordIndex] = u;
        mesh.texcoords[texcoordIndex + 1] = v;
    }
    
    model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].value = 1.0f;
    
    rlTextureParameters(texture.id, RL_TEXTURE_WRAP_S, RL_TEXTURE_WRAP_REPEAT);
    rlTextureParameters(texture.id, RL_TEXTURE_WRAP_T, RL_TEXTURE_WRAP_REPEAT);
}

void Ground::Draw() {
    // Create a grid of ground segments
    for (int x = -2; x <= 2; x++) {      // Horizontal spread (left/right)
        for (int z = -2; z <= 2; z++) {  // Depth spread (forward/backward)
            DrawModel(
                model,
                (Vector3){ 
                    position.x + width/2 + (x * width),   // X offset
                    position.y,                           // Y stays the same
                    position.z + length/2 + (z * length)  // Z offset
                },
                1.0f,
                WHITE
            );
        }
    }
}

bool Ground::CheckCollision(const Vector3& point) const {
    // Проверяем, находится ли точка над землёй
    float groundLevel = position.y;
    
    // Учитываем размеры земли (5x5 сегментов)
    float totalWidth = width * 5;
    float totalLength = length * 5;
    float halfWidth = totalWidth / 2.0f;
    float halfLength = totalLength / 2.0f;
    
    // Проверяем, находится ли точка в пределах земли по X и Z
    bool withinX = (point.x >= -halfWidth && point.x <= halfWidth);
    bool withinZ = (point.z >= -halfLength && point.z <= halfLength);
    
    return withinX && withinZ && point.y <= groundLevel;
} 