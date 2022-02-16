#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

// #include "debug.h"
#include "shader.h"
// #include "vertexBuffer.h"
// #include "indexBuffer.h"
// #include "vertexArrayObject.h"
#include "camera.h"
#include "stb_image.h"
#include "model.h"
#include "renderer.h"
#include "texture.h"

int main(){
    // Setup Code
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string title = "OpenGL";
    window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    // GL Config
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // Set frame rate - enable VSync
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CCW);

    glewInit();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    // Main code
    Renderer renderer;
    Camera camera(window, glm::vec3(0, 0, 5), 45.0f);
    
    Shader basicShader("shaders/default.vshader","shaders/default.fshader");
    // basicShader.SendUniform("u_Color", 0.1f, 0.2f, 0.3f, 1.0f);
    basicShader.SendUniform("u_Color", 0.70f, 1.00f, 0.40f, 1.0f);
    
    renderer.AddModel("obj/monkey.obj");
    renderer.SetPosition(0, glm::vec3(5.0f, 0.0f, 0.0f));
    renderer.AddModel("obj/monkey.obj");
    renderer.SetPosition(1, glm::vec3(-5.0f, 0.0f, 0.0f));
    // Model monkey2("obj/lightCube.obj", glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    // Textures 
    /*
    */
    // int imgWidth, imgHeight, colorChanels;
    // unsigned char* bytes = stbi_load("textures/icon.png", &imgWidth, &imgHeight, &colorChanels, 0);
    // Texture testTexure(bytes, GL_TEXTURE0, imgWidth, imgHeight);
    // basicShader.SendUniform("text0", 0);
    // free(bytes);
    // send the texture slot to the GPU - uniform: tex0 = 0

    // FPS counter variables
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

    // Render Loop
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        // Background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // FPS counter
        crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

        if (timeDiff >= 1.0 / 30.0) {
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			// std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = title + " - " + FPS + " FPS";
			glfwSetWindowTitle(window, newTitle.c_str());

			prevTime = crntTime;
			counter = 0;
		}

        camera.Inputs(window);

        // Uniforms for lighting
        basicShader.Bind();
        basicShader.SendUniform("u_lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
        basicShader.SendUniform("u_lightPos", 0.0f, 5.0f, 3.0f);
        basicShader.SendUniform("u_camPos", camera.position.x, camera.position.y, camera.position.z);

        // Draw all objects
        renderer.DrawObjects(basicShader, camera);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    };

    glDeleteProgram(basicShader.GetID());
    glfwTerminate();
    return 0;
}