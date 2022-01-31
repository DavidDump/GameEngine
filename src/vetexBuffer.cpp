#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#include "vertexBuffer.h"
#include "debug.h"
#include "model.h"

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices) {
	GLCall(glGenBuffers(1, &id));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(std::vector<glm::mat4>& vertices) {
	GLCall(glGenBuffers(1, &id));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::mat4), vertices.data(), GL_STATIC_DRAW));
}

unsigned int VertexBuffer::GetID() {
	return id;
}

void VertexBuffer::Bind() {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Unbind() {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}