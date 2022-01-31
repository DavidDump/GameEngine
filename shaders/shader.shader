#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormals;
layout(location = 3) in vec3 aColor;

out vec3 fragmentColor;
out vec2 textCoord;
out vec3 normals;
out vec3 crntPos;

uniform mat4 u_MVP;
uniform mat4 u_modelMatrix;

void main() {
	gl_Position = u_MVP * vec4(aPos, 1.0f);
	
	fragmentColor = aColor;
	textCoord = aUV;
	normals = aNormals;

	crntPos = vec3(u_modelMatrix * vec4(aPos, 1.0f));
};

#shader fragment
#version 330 core

// need to import normals and pos from vertex
in vec3 normals;
in vec3 crntPos;
in vec3 fragmentColor;
in vec2 textCoord;
out vec4 color;

uniform vec4 u_Color;
uniform sampler2D tex0;
uniform vec3 u_lightPos;
uniform vec4 u_lightColor;
uniform vec3 u_camPos;

float AmbientVal(){
	return 0.2f;
}

float DiffuseVal(){
	vec3 normal = normalize(normals);
	vec3 lightDirection = normalize(u_lightPos - crntPos);
	return max(dot(normal, lightDirection), 0.0f);
}

float SpecularVal(){
	float specularLight = 0.50f;
	vec3 normal = normalize(normals);
	vec3 viewDirection = normalize(u_camPos - crntPos);
	vec3 lightDirection = normalize(u_lightPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	return specAmount * specularLight;
}

void main() {
	// color = texture(tex0, textCoord);
	// color = vec4(fragmentColor, 1.0f);
	// color = u_Color;

	// needed: u_lightColor, u_lightPos, u_modelMatrix, u_camPos
	// color = u_Color * u_lightColor * (AmbientVal() + DiffuseVal() + SpecularVal());
	color = texture(tex0, textCoord) * u_lightColor * (AmbientVal() + DiffuseVal() + SpecularVal());
};