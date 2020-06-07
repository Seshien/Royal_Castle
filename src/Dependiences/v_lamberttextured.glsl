#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
layout (location=0) in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec3 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wspó³rzêdne teksturowania


//Zmienne interpolowane
out vec2 i_tc;
out vec3 i_nl;
out vec3 i_coords;


void main() 
{
    i_nl = normal;
    i_tc = texCoord;
    i_coords = vec3(M * vec4(vertex, 1.0));
    gl_Position = P * V * M * vec4(vertex, 1.0);
}