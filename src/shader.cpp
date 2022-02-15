#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <iostream>
// #include <sstream>

#include "shader.h"
#include "debug.h"

Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
    // shadersRAW = ParseShader(path);
    vertex = LoadShader(vertPath);
    fragment = LoadShader(fragPath);
    shader = CreateShader(vertex, fragment);
    Bind();
}

unsigned int Shader::GetID() {
    return shader;
}

std::string Shader::GetVertex(){
    return vertex;
}

std::string Shader::GetFragment(){
    return fragment;
}

std::string Shader::LoadShader(const std::string& path){
    std::fstream input(path);

    std::string line;
    std::string shader;

    if(input.is_open()){
        while(getline(input, line)){
            shader.append(line.c_str());
            shader.append("\n");
        }
    }
    return shader;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    //Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == false) {
        int lenght;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        char* messege = (char*)alloca(lenght * sizeof(char));
        GLCall(glGetShaderInfoLog(id, lenght, &lenght, messege));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << messege << std::endl;
        GLCall(glDeleteShader(id));

        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() {
    GLCall(glUseProgram(shader));
}

void Shader::SendUniform(const char *name, const float &v1, const float& v2, const float& v3, const float& v4 = 1.0f) {
    GLCall(glUniform4f(glGetUniformLocation(shader, name), v1, v2, v3, v4));
}

void Shader::SendUniform(const char* name, glm::mat4 matrix) {
    GLCall(glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SendUniform(const char* name, unsigned int id) {
    GLCall(glUniform1i(glGetUniformLocation(shader, name), id));
}

void Shader::SendUniform(const char *name, const float &v1, const float& v2, const float& v3) {
    GLCall(glUniform3f(glGetUniformLocation(shader, name), v1, v2, v3));
}