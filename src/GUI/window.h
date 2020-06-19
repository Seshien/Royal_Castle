#pragma once


#include <iostream>
#include <random>

#include<glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "..\constants.h"
#include "shaderprogram.h"
#include "modelTemplate.h"
#include "model.h"
#include "camera.h"
#include "init_castle.h"


void ChangeViewSize_call(GLFWwindow* window, int width, int height);
void ProcessMouse_call(GLFWwindow* window, double xpos, double ypos);
struct Particle
{
	glm::vec3 position;
	glm::vec3 speed;
	float ttl;
};
class Window
{

public:
	Window();

	bool StartWindow();
	void ChangeViewSize(GLFWwindow* window, int width, int height);
	void ProcessMouse(GLFWwindow* window, double xpos, double ypos);

	std::unique_ptr<InitCastle> initcastle;
	std::unique_ptr<Camera> camera_ptr;
	GLFWwindow* window_ptr;
    std::shared_ptr<ShaderProgram> TexturedShader;
	std::shared_ptr<ShaderProgram> ColorShader;
	void create_Particle();

	void ProcessSystem();
	int ilosc = 10000;
	glm::vec3 gravity = glm::vec3(0, 1, 0);

	void initializeSystem();

private:

	GLfloat scale_x, scale_y, scale_z, pos_x, pos_y, pos_z;
	void RenderWindow();

	void GLFWInit();
	bool WindowInit();
	bool GladInit();
	bool ShadersInit();
	bool ObjectsInit();

	//void CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader);

//	std::shared_ptr<ModelTemplate> FindTemplate(std::string name);

//	void CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color);

	void ProcessInput();

	void ProcessOther();

	void ProcessObjectMovement();

	void ClearWindow();

	void ProcessMovement();

	std::vector<Particle> system;

	ShaderProgram *sp;
	std::vector<Model> objects;
	std::vector<std::shared_ptr<ModelTemplate>> modelTemplates;
	std::unique_ptr<Model> player_ptr;
	std::vector<Light> lights;
	float timer;
	float frameTime;
	float lastFrameTime;
	int handled;
	bool editorMode;
	bool clicker;


};


