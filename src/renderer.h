#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "debug.h"

class Renderer
{
public:
	unsigned int Create3DObject(const float *vertex[], const unsigned int *index[]) {
        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));
        
        unsigned int vertexBuffer;
        GLCall(glGenBuffers(1, &vertexBuffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW));

        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
        GLCall(glEnableVertexAttribArray(0));

        unsigned int indexBuffer;
        GLCall(glGenBuffers(1, &indexBuffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW));

        Unbind();

        return vao;
	}

    void Unbind() {
        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void DrawVAO(const unsigned int &vao, float index[]) {
        GLCall(glBindVertexArray(vao));
        GLCall(glDrawElements(GL_TRIANGLES, sizeof(index) / sizeof(float), GL_UNSIGNED_INT, nullptr));
    }

    void DrawTriangle(const float &x1, const float &y1, const float& x2, const float& y2, const float& x3, const float& y3) {
        Unbind();
        float vertex[] = {
            x1, y1,
            x2, y2,
            x3, y3
        };

        unsigned int index[] = {0, 1, 2};

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        unsigned int vertexBuffer;
        GLCall(glGenBuffers(1, &vertexBuffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
        GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertex, GL_STATIC_DRAW));

        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
        GLCall(glEnableVertexAttribArray(0));

        unsigned int indexBuffer;
        GLCall(glGenBuffers(1, &indexBuffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), index, GL_STATIC_DRAW));

        GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

        Unbind();
    }
};