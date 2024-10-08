#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 tTexture;
out vec3 tNormal;
out vec3 tFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    tFragPos = vec3(model * vec4(position, 1.0f));
    tNormal = mat3(transpose(inverse(model))) * normal;
    tTexture = texCoords;
}