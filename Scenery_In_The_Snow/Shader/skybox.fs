#version 330

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 ambientLight;

void main()
{
    FragColor = vec4(ambientLight, 1) * texture(skybox, TexCoords);
}