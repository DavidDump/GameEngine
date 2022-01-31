#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>

#include "indexBuffer.h"
#include "debug.h"

IndexBuffer::IndexBuffer(std::vector<unsigned int>& indices) {
    GLCall(glGenBuffers(1, &id));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
}

unsigned int IndexBuffer::GetID() {
    return id;
}

void IndexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}