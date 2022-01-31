#pragma once
#ifndef SHADER_H
#define SHADER_H

#ifndef _IOSTREAM_
#include <iostream>
#endif

struct ShaderSources {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
    private:
        ShaderSources shadersRAW;
        unsigned int shader;

    public:
        Shader(const std::string& path);

        // Return shader ID
        unsigned int GetID();

        // Return shader raw string
        ShaderSources GetShaderRAW();

        // Parse the shader input into the vertex and fragment shader
        ShaderSources ParseShader(const std::string& path);

        // Compile a single shader
        unsigned int CompileShader(unsigned int type, const std::string& source);

        // Create the shader program from the vertex and fragment shader
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        // Bind the shader
        void Bind();

        // Send a uniform to shader of type vec4
        void SendUniform(const char *name, const float &v1, const float& v2, const float& v3, const float& v4);

        // Send a uniform to shader of type mat4
        void SendUniform(const char* name, glm::mat4 matrix);
        
        // Send a uniform to shader of type uint
        void SendUniform(const char* name, unsigned int id);

        // Send a uniform to shader of type vec3
        void SendUniform(const char *name, const float &v1, const float& v2, const float& v3);
};

#endif