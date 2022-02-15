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
	color = u_Color * u_lightColor * (AmbientVal() + DiffuseVal() + SpecularVal());
	// color = texture(tex0, textCoord) * u_lightColor * (AmbientVal() + DiffuseVal() + SpecularVal());
};