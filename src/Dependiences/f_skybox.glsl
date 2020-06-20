#version 330 core


out vec4 pixelColor;
in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    pixelColor = texture(skybox, TexCoords);
}