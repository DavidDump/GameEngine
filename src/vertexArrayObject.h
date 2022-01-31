#pragma once
#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

class VertexArrayObject {
	private:
		unsigned int id;

	public:
		// Constructor initialize VBO
		VertexArrayObject();

		// Bind VBO
		void Bind();

		// Unbind VBO
		void Unbind();

		// Specify the currently bound vertex buffer layout
		void SetVertexBufferLayout(int index, int vecSize, int startPoint);
};

#endif