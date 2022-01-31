#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera(GLFWwindow* window, glm::vec3 pos, float fov){
	position = pos;
	fFOV = fov;
	int ScreenWidth, ScreenHeight;
	glfwGetFramebufferSize(window, &ScreenWidth, &ScreenHeight);
    float fAspectRatio = (float)ScreenWidth / (float)ScreenHeight;

	ProjectionMatrix = glm::perspective(glm::radians(fFOV), fAspectRatio, fNear, fFar);
}

void Camera::Inputs(GLFWwindow* window) {
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	
	int ScreenWidth, ScreenHeight;
	glfwGetFramebufferSize(window, &ScreenWidth, &ScreenHeight);

	if(fistFrame){
		glfwSetCursorPos(window, ScreenWidth / 2, ScreenHeight / 2);
		fistFrame = false;
	}

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	
	glfwSetCursorPos(window, ScreenWidth / 2, ScreenHeight / 2);

	// Compute new orientation
	float rotX = mouseSensitivity * (float)(ypos - (ScreenHeight / 2)) / ScreenHeight;
	float rotY = mouseSensitivity * (float)(xpos - (ScreenWidth / 2)) / ScreenWidth;

	// Vertical camera rotation
	glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

	// Clamp the vertical camera rotation
	if(abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)){
		orientation = newOrientation;
	}

	// Horizontal rotation combined with verical
	orientation = glm::rotate(orientation, glm::radians(-rotY), up);

	// Calculate right vector
	glm::vec3 right = glm::normalize(glm::cross(orientation, up));

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += orientation * deltaTime * camSpeed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= orientation * deltaTime * camSpeed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * camSpeed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * camSpeed;
	}
	// Move up
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		position += up * deltaTime * camSpeed;
	}
	// Move down
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
		position -= up * deltaTime * camSpeed;
	}

	// Camera matrix
	viewMatrix = glm::lookAt(
		position,               // Camera is here
		position + orientation, // and looks here : at the same position, plus "direction"
		up                      // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

glm::mat4 Camera::GetViewMatrix(){
	viewMatrix = glm::lookAt(
		position,               // Camera is here
		position + orientation, // and looks here : at the same position, plus "direction"
		up                      // Head is up (set to 0,-1,0 to look upside-down)
	);

	return viewMatrix;
}