#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

// #include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#ifndef _glfw3_h_
#include <GLFW/glfw3.h>
#endif

class Camera{
    private:
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        
        float camSpeed = 3.0f;
        float mouseSensitivity = 100.0f;
        bool fistFrame = true;

        float fNear = 0.1f;
        float fFar = 100.0f;
        float fFOV = 45.0f;

    public:
        glm::mat4 ProjectionMatrix;
        glm::mat4 viewMatrix;
        glm::vec3 position = glm::vec3(0, 0, 5);
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        
        // Constructor, set the configurations for the camera
        Camera(GLFWwindow* window, glm::vec3 pos, float fov);

        // Function for all the movement
        void Inputs(GLFWwindow* window);

        // Calculates the view matrix 
        glm::mat4 GetViewMatrix();
};

#endif