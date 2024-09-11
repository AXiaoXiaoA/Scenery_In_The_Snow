#version 330 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec2 vTexture;
layout( location = 2 ) in vec3 vNormal;

out vec2 tTexture;
out vec3 tFragPos;
out vec3 tNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(vPosition, 1.0);
	tTexture = vTexture;
	tFragPos = vec3(model * vec4(vPosition, 1.0));
	tNormal = mat3(transpose(inverse(model))) * vNormal;
}