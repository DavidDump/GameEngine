#pragma once
#ifndef SHADER_H
#define SHADER_H

#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _STRING_
#include <string>
#endif


class Shader {
    private:
        // ShaderSources shadersRAW;
        std::string vertex;
        std::string fragment;
        unsigned int shader;

    public:
        // Constructor
        Shader(const std::string& vertPath, const std::string& fragPath);

        // Return shader ID
        unsigned int GetID();

        // Return vertex shader raw string
        std::string GetVertex();

        // Return fragment shader raw string
        std::string GetFragment();

        // Load a shader from file and return it
        std::string LoadShader(const std::string& path);

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