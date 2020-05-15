#pragma once
#include "model.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class static_object : public Model
{
public:
	std::string path;
	glm::vec3 position, scale, rotate;

	void load_model();
	static_object();
	static_object (std::string path, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate);
	void create_object();
	bool collision(glm::vec3);
};

