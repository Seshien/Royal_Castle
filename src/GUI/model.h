#pragma once
#include <iostream>

#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <math.h>
#include "modelTemplate.h"

class Model
{
public:
	Model(std::shared_ptr<ModelTemplate> parent, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color);

	bool Collision(glm::vec3 pos);
	void Draw();
	void DrawWire();


	void ChangePosition(glm::vec3 movement);
	void SetPosition(glm::vec3 position);

	void ChangeScale(glm::vec3 scale);
	void SetScale(glm::vec3 scale);

	void ChangeRotation(glm::vec3 rotate, float angle);
	void SetRotation(glm::vec3 rotate, float angle);



	void SetMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle);
	void SetMatrix(glm::mat4 _mat) { this->mat = -mat; }
	glm::mat4 GetMatrix() { return this->mat; }
	glm::mat4 GetInvMatrix() { return this->invMat; }
	glm::vec3 GetColor() { return this->color; }

	std::shared_ptr<ModelTemplate> GetParent() { return parent; }
	glm::vec3 GetPosition() { return position; }

private:


	void SetMatrix();

	std::shared_ptr<ModelTemplate> parent;

	glm::mat4 mat;
	glm::mat4 invMat;
	glm::vec3 color;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;
};

