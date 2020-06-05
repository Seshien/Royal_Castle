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

class InitCastle
{
public:
	InitCastle();
	void CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color);
	void CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader);
	std::shared_ptr<ModelTemplate> FindTemplate(std::string name);

	std::unique_ptr<Model> LoadPlayer();
	std::vector<std::shared_ptr<ModelTemplate>> LoadTemplates(std::shared_ptr<ShaderProgram> shader);
	std::vector<Model> LoadObjects();
private:
	GLfloat scale_x, scale_y, scale_z, pos_x, pos_y, pos_z;
	std::vector<std::shared_ptr<ModelTemplate>> _modelTemplates;
	std::vector<Model> _objects;
	std::unique_ptr<Model> _player_ptr;
};