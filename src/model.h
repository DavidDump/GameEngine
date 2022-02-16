#ifndef MODEL_H
#define MODEL_H

// #include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>
#include "camera.h"
#include "shader.h"
#include "vertexArrayObject.h"

struct Vertex{
    glm::vec3 position;
    glm::vec2 textureUV;
    glm::vec3 normals;
    glm::vec3 color;
};

class Model{
    private:
        std::vector<glm::vec3> vertexData;
        std::vector<unsigned int> vertexIndexData;
        std::vector<glm::vec2> textureData;
        std::vector<unsigned int> textureIndexData;
        std::vector<glm::vec3> normalsData;
        std::vector<unsigned int> normalsIndexData;

        VertexArrayObject model;

        int instances;
        std::vector<glm::mat4> modelMatrices;
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indexes;

        glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        // glm::mat4 RotationMatrix = glm::mat4(1.0f);
        // glm::mat4 RotationMatrix = glm::mat4_cast(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
        glm::mat4 RotationMatrix = glm::eulerAngleXYZ(1.0f, 0.0f, 0.0f);
        glm::mat4 ScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));


        // Construction for model set the position, rotation, and scale
        // Model(const char* path, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
        // Constructor for instanced model
        Model(const char* path, int inst = 1, std::vector<glm::mat4> modelMat = {});

        // Draw the model
        void Draw(Shader shader, Camera camera);
        
        // Load a model from a file, supported formats: .obj
        void LoadModel(const char* path);

        // Set a color for every vertex
        void SetColor(glm::vec3 color);
};

#endif