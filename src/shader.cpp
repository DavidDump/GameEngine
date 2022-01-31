#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <iostream>
// #include <sstream>

#include "shader.h"
#include "debug.h"

Shader::Shader(const std::string& path) {
    shadersRAW = ParseShader(path);
    shader = CreateShader(shadersRAW.vertexSource, shadersRAW.fragmentSource);
    Bind();
}

unsigned int Shader::GetID() {
    return shader;
}

ShaderSources Shader::GetShaderRAW() {
    return shadersRAW;
}

ShaderSources Shader::ParseShader(const std::string& path) {
    std::fstream shaderFile(path);

    int type = -1;
    std::string vertexShader;
    std::string fragmentShader;
    std::string line;

    if (shaderFile.is_open()) {
        while (getline(shaderFile, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = 0;
                }
                else if (line.find("fragment") != std::string::npos) {
                    type = 1;
                }
            }
            else if (type == 0) {
                vertexShader.append(line.c_str());
                vertexShader.append("\n");
            }
            else if (type == 1) {
                fragmentShader.append(line.c_str());
                fragmentShader.append("\n");
            }
        }
    }
    else {
        std::cout << "Failed to open " << path << " shader file." << std::endl;
        return {};
    }

    return { vertexShader, fragmentShader };
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