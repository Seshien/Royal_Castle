#pragma once
#include<glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
class Window
{
public:
	Window();

	bool StartWindow();
	static void ChangeViewSize(GLFWwindow* window, int width, int height);
	GLFWwindow* window_ptr;
private:
	void Init();
	bool CreateGlad();
	void processInput();

	bool CreateWindow();

};

