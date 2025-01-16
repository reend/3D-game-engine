#include "ModelLoader.hpp"

ModelLoader::ModelLoader() : position(0.0f, 0.0f, 0.0f) {}

bool ModelLoader::LoadFromFile(const std::string& path) {
    if (!FileExists(path.c_str())) {
        TraceLog(LOG_ERROR, "Model file not found: %s", path.c_str());
        return false;
    }
    
    model = LoadModel(path.c_str());
    return model.meshCount > 0;
}

void ModelLoader::Update() {
    position.y += 1.0f * GetFrameTime();
}

void ModelLoader::Draw() {
    model.Draw(position, 1.0f, RED);
} 