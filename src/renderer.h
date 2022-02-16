#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glm/vec3.hpp>
#include <vector>
#include "model.h"
#include "shader.h"
#include "camera.h"

class Renderer {
    std::vector<Model> objects;
    public:
        // Add a model to the list of all to be rendered
        void AddModel(const char* path);

        // Draw all the objects
        void DrawObjects(Shader shader, Camera camera);

        void SetPosition(int id, glm::vec3 pos);
        void SetRotiation(int id, glm::vec3 rot);
        void SetScale(int id, glm::vec3 scale);
};

#endif