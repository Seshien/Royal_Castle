#pragma once
#include <string>
#include <vector>

#include "shaderprogram.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "..\Dependiences\stb_image.h"
#include <memory>
#include <iostream>

class Skybox
{


public:

	Skybox(std::string path, std::shared_ptr<ShaderProgram> _shader);
	void Draw();


	std::vector<float> skyboxVertices;
	unsigned int texture;

private:
	unsigned int VAO, VBO;

	std::shared_ptr<ShaderProgram> shader;
	unsigned int loadCubemap(std::string path);

};

