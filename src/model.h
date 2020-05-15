
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "constants.h"



	class Model {
	public:
		std::vector<float> vertices, vertexNormals, texCoords, cuboid;
		glm::vec4 cuboid_ver;
		glm::mat4 Mat;
		void change_cuboid();
		void create_cuboid();
		float wierzcholki[6] = { 0 }; //max x, max y, max z, min x, min y, min z
		void drawSolid();
		virtual bool collision(glm::vec3) = 0;
	};


#endif
