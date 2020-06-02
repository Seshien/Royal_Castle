#pragma once

#include <string>
#include <vector>

#include "shaderprogram.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include <memory>

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
	glm::vec3 min;
	glm::vec3 max;

	//float* colors;

	void drawSolid(std::shared_ptr<ShaderProgram> shader);
	void drawWire(std::shared_ptr<ShaderProgram> shader);
	bool Collision(glm::vec3 pos, glm::mat4 mat);
private:


	unsigned int VAO, VBO, EBO;
	void initMesh();
	void findMinMax();
	void Draw(std::shared_ptr<ShaderProgram> shader);
	

};

