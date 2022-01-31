#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.h"
#include "camera.h"
#include "shader.h"
#include "vertexArrayObject.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "debug.h"

// Cut the string in two at the first appearance of the delimiter
std::pair<std::string, std::string> substring(std::string str, char delim){
    std::pair<std::string, std::string> retVal;
    int index = str.find(delim);
    retVal.first = str.substr(0, index);
    retVal.second = str.substr(index + 1);

    return retVal;
}

Model::Model(const char* path, int inst, std::vector<glm::mat4> modelMat){
    // TranslationMatrix = glm::translate(glm::mat4(1.0f), pos);
    // RotationMatrix = glm::mat4(1.0f);
    // ScalingMatrix = glm::scale(glm::mat4(1.0f), scale);
    instances = inst;
    modelMatrices = modelMat;

    LoadModel(path);

    model.Bind();
    VertexBuffer vertexBuffer(vertices);
    IndexBuffer indexBuffer(indexes);
    model.SetVertexBufferLayout(0, 3, offsetof(Vertex, position)); // position
    model.SetVertexBufferLayout(1, 2, offsetof(Vertex, textureUV)); // textureUV
    model.SetVertexBufferLayout(2, 3, offsetof(Vertex, normals)); // normals
    model.SetVertexBufferLayout(3, 3, offsetof(Vertex, color)); // color

    // VertexBuffer modelMatrixBuffer(modelMatrices);
    // if(instances != 1){
    //     model.SetVertexBufferLayout(4, 4, 0 * sizeof(glm::vec4));
    //     model.SetVertexBufferLayout(5, 4, 1 * sizeof(glm::vec4));
    //     model.SetVertexBufferLayout(6, 4, 2 * sizeof(glm::vec4));
    //     model.SetVertexBufferLayout(7, 4, 3 * sizeof(glm::vec4));

    //     // Dont know what this means - "Makes it so the transform is only switched when drawing the next instance"
    //     glVertexAttribDivisor(4, 1);
	// 	glVertexAttribDivisor(5, 1);
	// 	glVertexAttribDivisor(6, 1);
	// 	glVertexAttribDivisor(7, 1);
    // }

    model.Unbind();
    vertexBuffer.Unbind();
    // modelMatrixBuffer.Unbind();
    indexBuffer.Unbind();
}

void Model::Draw(Shader shader, Camera camera){
    glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
    
    glm::mat4 MVPMatrix = camera.ProjectionMatrix * camera.GetViewMatrix() * ModelMatrix;

    shader.Bind();
    shader.SendUniform("u_MVP", MVPMatrix);

    model.Bind();
    // shader.Bind();
    if(instances == 1){
        GLCall(glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, nullptr));
    }else {
        GLCall(glDrawElementsInstanced(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0, instances));
    }
    // model.Unbind();
}

void Model::LoadModel(const char* path){
    std::string buffer;
    std::ifstream input;
    input.open(path);

    if(!input.is_open()){
        std::cout << "[ERROR] And error has occured while loading a model file" << std::endl;
        std::cout << "Error location: " << __FILE__ << " line number: " << __LINE__ << std::endl;
        return;
    }
    
    // std::string asd = "//123";
    // std::cout << "first: \"" << substring(asd, '/').first <<  "\" second: " <<  "\"" << substring(asd, '/').second << "\"" << std::endl;

    std::getline(input, buffer);
    while(!input.eof()){
        // ignore comments and such
        if(buffer[0] != 'v' && buffer[0] != 'f'){
            std::getline(input, buffer);
            continue;
        }
        if(buffer.find("v ") != std::string::npos){
            // store vertex data
            std::size_t index;

            index = buffer.find(' ');
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str1 = buffer.substr(0, index);
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str2 = buffer.substr(0, index);
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str3 = buffer.substr(0, index);

            vertexData.push_back(glm::vec3(std::stof(str1), std::stof(str2), std::stof(str3)));
        }else if(buffer.find("vt ") != std::string::npos){
            // store UVs/texture data
            std::size_t index;

            index = buffer.find(' ');
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str1 = buffer.substr(0, index);
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str2 = buffer.substr(0, index);

            textureData.push_back(glm::vec2(std::stof(str1), std::stof(str2)));
        }else if(buffer.find("vn ") != std::string::npos){
            // store normals
            std::size_t index;

            index = buffer.find(' ');
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str1 = buffer.substr(0, index);
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str2 = buffer.substr(0, index);
            buffer = buffer.substr(index + 1, std::string::npos);
            index = buffer.find(' ');
            std::string str3 = buffer.substr(0, index);

            normalsData.push_back(glm::vec3(std::stof(str1), std::stof(str2), std::stof(str3)));
        }else if(buffer.find("f ") != std::string::npos){
            // store index data
            std::pair<std::string, std::string> str = substring(substring(buffer, ' ').second, ' ');
            std::pair<std::string, std::string> data = substring(str.first, '/');
            vertexIndexData.push_back(std::stoi(data.first) - 1);
            textureIndexData.push_back(std::stoi(substring(data.second, '/').first) - 1);
            normalsIndexData.push_back(std::stoi(substring(data.second, '/').second) - 1);

            str = substring(str.second, ' ');
            data = substring(str.first, '/');
            vertexIndexData.push_back(std::stoi(data.first) - 1);
            textureIndexData.push_back(std::stoi(substring(data.second, '/').first) - 1);
            normalsIndexData.push_back(std::stoi(substring(data.second, '/').second) - 1);

            str = substring(str.second, ' ');
            data = substring(str.first, '/');
            vertexIndexData.push_back(std::stoi(data.first) - 1);
            textureIndexData.push_back(std::stoi(substring(data.second, '/').first) - 1);
            normalsIndexData.push_back(std::stoi(substring(data.second, '/').second) - 1);

            // code for loading .objs that only have vertex positions and are missing uvs and normals
            // std::size_t index;

            // index = buffer.find(' ');
            // buffer = buffer.substr(index + 1, std::string::npos);
            // index = buffer.find(' ');
            // std::string str1 = buffer.substr(0, index);
            // buffer = buffer.substr(index + 1, std::string::npos);
            // index = buffer.find(' ');
            // std::string str2 = buffer.substr(0, index);
            // buffer = buffer.substr(index + 1, std::string::npos);
            // index = buffer.find(' ');
            // std::string str3 = buffer.substr(0, index);

            // model.indexData.push_back(glm::vec3(std::stoi(str1) - 1.0f, std::stoi(str2) - 1.0f, std::stoi(str3) - 1.0f));
            // vertexIndexData.push_back(std::stoi(str1) - 1);
            // vertexIndexData.push_back(std::stoi(str2) - 1);
            // vertexIndexData.push_back(std::stoi(str3) - 1);
        }
        std::getline(input, buffer);
    }

    for(unsigned int i = 0; i < vertexIndexData.size(); i++){
        vertices.push_back(Vertex{
            vertexData[vertexIndexData[i]],     // position
            textureData[textureIndexData[i]],   // UVs
            normalsData[normalsIndexData[i]],   // normals
            glm::vec3(1.0f, 1.0f, 1.0f)         // color
        });
        indexes.push_back(i);
    }

    input.close();
    return;
}

void Model::SetColor(glm::vec3 color){
    for(unsigned int i = 0; i < vertices.size(); i++){
        vertices[i].color = color;
    }
}