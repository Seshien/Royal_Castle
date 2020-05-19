#pragma once

#include <string>
#include <vector>

#include "src\GUI\shaderprogram.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{

public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	int vertexCount;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//float* colors;

	void drawSolid();
	void drawWire();
private:


	unsigned int VAO, VBO, EBO;
	void initMesh();

	void draw();


};

