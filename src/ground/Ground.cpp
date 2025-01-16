#include "Ground.hpp"
#include "rlgl.h"

Ground::Ground() {
    width = 1024.0f;  
    length = 1024.0f;
    
    position = {
        -width / 2.0f,  
        -5.0f,          
        -length / 2.0f  
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
        
        mesh.texcoords[texcoordIndex] = u * 20.0f;
        mesh.texcoords[texcoordIndex + 1] = v * 20.0f;
    }
    
    model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].value = 1.0f;
    
    rlTextureParameters(texture.id, RL_TEXTURE_WRAP_S, RL_TEXTURE_WRAP_REPEAT);
    rlTextureParameters(texture.id, RL_TEXTURE_WRAP_T, RL_TEXTURE_WRAP_REPEAT);
}

void Ground::Draw() {
    DrawModel(
        model,
        (Vector3){ position.x + width/2, position.y, position.z + length/2 },
        1.0f,
        WHITE
    );
} 