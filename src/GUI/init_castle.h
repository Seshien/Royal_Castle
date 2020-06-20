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
#include "skybox.h"

struct Light {
	glm::vec3 pos;
	glm::vec3 color;
};
class InitCastle
{
public:
	int n;
	Light sources[256];
	
	InitCastle(std::shared_ptr<ShaderProgram> shader);
	void CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color, bool, glm::vec3);
	void CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader);
	void CreateSources(glm::vec3, glm::vec3);

	std::shared_ptr<ModelTemplate> FindTemplate(std::string name);

	std::unique_ptr<Model> LoadPlayer();
	std::vector<std::shared_ptr<ModelTemplate>> LoadTemplates();
	std::vector<Model> LoadObjects();
	std::vector<Light> LoadLights();
	std::shared_ptr<Skybox> LoadSkybox(std::shared_ptr<ShaderProgram> shader);


private:
	std::vector<Light> _lights;
	GLfloat scale_x, scale_y, scale_z, pos_x, pos_y, pos_z;
	std::vector<std::shared_ptr<ModelTemplate>> _modelTemplates;
	std::vector<Model> _objects;
	std::unique_ptr<Model> _player_ptr;
};