#pragma once
#ifndef INDEX_BUFFER_H
#define INDEX_BUFER_H

#ifndef _VECTOR_
#include <vector>
#endif

// Buffer to store all the index data
class IndexBuffer {
	private:
		unsigned int id;

	public:
		// Contructor initalize buffer with data
		IndexBuffer(std::vector<unsigned int>& indices);

		// Return index buffer ID
		unsigned int GetID();

		// Bind index buffer
		void Bind();

		// Unbind index buffer
		void Unbind();
};

#endif