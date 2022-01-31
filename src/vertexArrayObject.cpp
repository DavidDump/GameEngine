#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "vertexArrayObject.h"
#include "debug.h"
#include "model.h"

VertexArrayObject::VertexArrayObject() {
	GLCall(glGenVertexArrays(1, &id));
	GLCall(glBindVertexArray(id));
}

void VertexArrayObject::Bind() {
	GLCall(glBindVertexArray(id));
}

void VertexArrayObject::Unbind() {
	GLCall(glBindVertexArray(0));
}

void VertexArrayObject::SetVertexBufferLayout(int index, int vecSize, int startPoint) {
	// index - the layout id to bind it to in GLSL 
	// size(vecSize) - the number of floats to read, vec3 - 3 floats for pos
	// type - type of the data provided
	// normalize - whether values should be normalized
	// stride - how many bytes to jump over to get to the next value, pos[0] + stride = pos[1]
	// pointer - pointer to the starting offset
	GLCall(glVertexAttribPointer(index, vecSize, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)startPoint));
	GLCall(glEnableVertexAttribArray(index));
}