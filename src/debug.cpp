#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall() {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << ")" << std::endl;
        return false;
    }
    return true;
}

void PrintError(int line, const char* file){
    std::cout << "[ERROR] And error has occured on line: " << line << " in file: " << file << std::endl;
}