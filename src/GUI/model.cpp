#include "model.h"


Model::Model(std::shared_ptr<ModelTemplate> parent, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color)
{
	this->parent = parent;
	this->color = color;
	SetMatrix(position, scale, rotate, angle);
	
}



void Model::Draw()
{
	this->parent->Draw();
}

void Model::DrawWire()
{
	this->parent->DrawWire();
}

bool Model::Collision(glm::vec3 pos)
{
	return this->parent->Collision(pos, mat);
}

void Model::ChangePosition(glm::vec3 movement)
{
	mat = glm::translate(mat, movement);
	this->position += movement;
}

void Model::SetPosition(glm::vec3 position)
{
	this->position = position;
	SetMatrix();
}

void Model::ChangeScale(glm::vec3 scale)
{
	mat = glm::scale(mat, scale);
	this->scale += scale;
}

void Model::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	SetMatrix();
}

void Model::ChangeRotation(glm::vec3 rotate, float angle)
{
	mat = glm::rotate(mat, angle, rotate);
	this->rotation += rotate;
	this->angle += angle;
}

void Model::SetRotation(glm::vec3 rotate, float angle)
{
	this->rotation = rotate;
	this->angle = angle;
	SetMatrix();

}

void Model::SetMatrix()
{
	mat = glm::translate(glm::mat4(1.0f), position);
	mat = glm::rotate(mat, angle, rotation);
	mat = glm::scale(mat, scale);
	invMat = glm::inverseTranspose(mat);
}

void Model::SetMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle)
{
	this->position = position;
	this->rotation = rotate;
	this->scale = scale;
	this->angle = angle;
	SetMatrix();
}
