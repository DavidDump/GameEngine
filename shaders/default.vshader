#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormals;
layout(location = 3) in vec3 aColor;

out vec3 fragmentColor;
out vec2 textCoord;
out vec3 normals;
out vec3 crntPos;

uniform mat4 u_ModelViewMatrix;
uniform mat4 u_CameraMatrix;
uniform mat4 u_ProjectionMatrix;

void main() {
	gl_Position = u_ProjectionMatrix * u_CameraMatrix * u_ModelViewMatrix * vec4(aPos, 1.0f);
	
	fragmentColor = aColor;
	textCoord = aUV;
	normals = aNormals;

	crntPos = vec3(u_ModelViewMatrix * vec4(aPos, 1.0f));
};