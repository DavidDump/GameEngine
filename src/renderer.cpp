#include "renderer.h"
#include "model.h"
#include "shader.h"
#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

int Renderer::AddModel(const char* path){
    Model obj(path);
    objects.push_back(obj);

    return objects.size() - 1;
}

void Renderer::DrawObjects(Shader shader, Camera camera){
    for(unsigned int i = 0; i < objects.size(); i++){
        objects[i].Draw(shader, camera);
    }
}

Model Renderer::GetModel(int id){
    return objects[id];
}

void Renderer::SetModelPosition(int id, glm::vec3 pos){
    objects[id].SetPosition(pos);
}

void Renderer::SetModelRotiation(int id, glm::vec3 rot){
    objects[id].SetRotiation(rot);
}

void Renderer::SetModelScale(int id, glm::vec3 scale){
    objects[id].SetScale(scale);
}