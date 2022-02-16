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
        // Add a model to the list of all to be rendered, returns the id of the model
        int AddModel(const char* path);

        // Draw all the objects
        void DrawObjects(Shader shader, Camera camera);

        // Return a model with id
        Model GetModel(int id);

        // Set the position of the model
        void SetModelPosition(int id, glm::vec3 pos);

        // Set the rotation of the model
        void SetModelRotiation(int id, glm::vec3 rot);

        // Set the scale of the model
        void SetModelScale(int id, glm::vec3 scale);
};

#endif