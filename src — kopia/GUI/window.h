#pragma once



#include <iostream>
#include <random>

//#include "..\Outside\include\glad\glad.h"
//#include "..\Outside\include\GLFW\glfw3.h"
//#include "..\Outside\include\glm\glm.hpp"
//#include "..\Outside\include\glm\ext.hpp"

#include<glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "shaderprogram.h"
#include "..\Temporary\modelWIP.h"
#include "..\model.h"
#include "..\static_object.h"
#include "camera.h"


void ChangeViewSize_call(GLFWwindow* window, int width, int height);
void ProcessMouse_call(GLFWwindow* window, double xpos, double ypos);

class Window
{
public:
	Window();

	bool StartWindow();
	void ChangeViewSize(GLFWwindow* window, int width, int height);
	void ProcessMouse(GLFWwindow* window, double xpos, double ypos);

	std::unique_ptr<Camera> camera_ptr;
	GLFWwindow* window_ptr;
	std::unique_ptr<ShaderProgram> myShader;
private:

	void RenderWindow();

	void GLFWInit();
	bool WindowInit();
	bool GladInit();
	bool ShadersInit();
	bool ObjectsInit();

	void ProcessInput();


	void ClearWindow();

	std::vector<static_object*> objects;
	std::vector<ModelWIP> models;
	float timer;
	float frameTime;
	float lastFrameTime;
};


