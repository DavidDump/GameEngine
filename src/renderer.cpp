#include "renderer.h"
#include "model.h"
#include "shader.h"
#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

void Renderer::AddModel(const char* path){
    Model obj(path);
    objects.push_back(obj);
}

void Renderer::DrawObjects(Shader shader, Camera camera){
    for(unsigned int i = 0; i < objects.size(); i++){
        objects[i].Draw(shader, camera);
    }
}

void Renderer::SetPosition(int id, glm::vec3 pos){
    objects[id].TranslationMatrix = glm::translate(glm::mat4(1.0f), pos);
}

void Renderer::SetRotiation(int id, glm::vec3 rot){
    objects[id].RotationMatrix = glm::eulerAngleXYZ(rot.x, rot.y, rot.z);
}

void Renderer::SetScale(int id, glm::vec3 scale){
    objects[id].ScalingMatrix = glm::scale(glm::mat4(1.0f), scale);
}