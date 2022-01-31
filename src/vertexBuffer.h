#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glm/mat4x4.hpp>
#ifndef _VECTOR_
#include <vector>
#endif
#include "model.h"

// Buffer to store all the vertex data
class VertexBuffer {
	private:
		unsigned int id;

	public:
		// Contructor initalize buffer with data
		VertexBuffer(std::vector<Vertex>& vertices);
		VertexBuffer(std::vector<glm::mat4>& vertices);

		// Return vertex buffer ID
		unsigned int GetID();

		// Bind vertex buffer
		void Bind();
		
		// Unbind vertex buffer
		void Unbind();
};

#endif