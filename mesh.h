#pragma once

#include <string>
#include <vector>

#include "src/GUI/shaderprogram.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

class Mesh
{
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture {
		unsigned int id;
		std::string type;
	};

public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	int vertexCount;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//float* colors;

	void drawSolid(ShaderProgram shader);
	void drawWire(ShaderProgram shader);
private:


	unsigned int VAO, VBO, EBO;
	void initMesh();

	void draw(ShaderProgram shader);


};

