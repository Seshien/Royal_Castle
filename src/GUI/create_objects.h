#pragma once
#include "model.h"
#include<glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "..\constants.h"
#include "shaderprogram.h"
#include "modelTemplate.h"
#include "camera.h"

class Create_objects
{
public:
	Create_objects();
	void CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color);
	void CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader);
	std::shared_ptr<ModelTemplate> FindTemplate(std::string name);
	
	std::vector<Model> objects;
	GLfloat scale_x, scale_y, scale_z, pos_x, pos_y, pos_z;
	std::shared_ptr<ShaderProgram> TexturedShader;
	std::vector<std::shared_ptr<ModelTemplate>> modelTemplates;
	std::unique_ptr<Model> player_ptr;
};