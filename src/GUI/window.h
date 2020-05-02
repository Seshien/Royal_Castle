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
#include "..\model.h"
#include "..\static_object.h"
#include "shaderprogram.h"




class Window
{
public:
	Window();

	bool StartWindow();
	static void ChangeViewSize(GLFWwindow* window, int width, int height);
	GLFWwindow* window_ptr;
private:

	void RenderWindow();

	void GLFWInit();
	bool WindowInit();
	bool GladInit();
	bool ShadersInit();

	void ProcessInput();

	void ChangeClearColor(float x, float y, float z, float a);

	void RandomClearColor();

	void ClearWindow();

	struct CameraCoords
	{
		float X = 0.0f;
		float Y = 0.0f;
		float Z = 5.0f;
	} cameraCoords;

};

