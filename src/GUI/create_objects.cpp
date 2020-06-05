#include "create_objects.h"

Create_objects::Create_objects()
{
	CreateTemplate("data\\cube.obj", "cube", TexturedShader);
	CreateTemplate("data\\cube_2.obj", "cube_2", TexturedShader);
	CreateTemplate("data\\medix`eval-house.obj", "house", TexturedShader);
	CreateTemplate("data\\mur.obj", "mur", TexturedShader);
	CreateTemplate("data\\stragan.obj", "stragan", TexturedShader);
	scale_x = 0.2;
	scale_y = 0.2;
	scale_z = 0.2;

	// ty
	player_ptr = std::make_unique<Model>(FindTemplate("cube"), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 1.0f));

	//podloga

	CreateObject("cube_2", glm::vec3(-10 * scale_x, -0.45f, 40 * scale_z), glm::vec3(150 * scale_x, 0.1, 160 * scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	CreateObject("house", glm::vec3(50.4f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	//CreateObject("castle", glm::vec3(40.4f, 0.2f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	//mury

	CreateObject("mur", glm::vec3(140 * scale_x, 0 * scale_y, 40 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f));                                //0.0f, 0.0f, 0.0f
	CreateObject("mur", glm::vec3(0.0f, 0.0f, -120 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));                                //-1.0f, 0.0f, 13.5f
	CreateObject("mur", glm::vec3(-160 * scale_x, 0.0f, 40 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 1.0f, 0.0f));                           //13.5f, 0.0f, 14.5f
	CreateObject("mur", glm::vec3(-20 * scale_x, 0.0f, 200 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI * 3 / 2, glm::vec3(0.0f, 1.0f, 0.0f));                    //14.5f, 0.0f, 1.0f

	//stragany
	scale_x = 0.3;
	scale_y = 0.3;
	scale_z = 0.3;
	for (int i = 0; i < 20; i += 3)
	{
		CreateObject("stragand", glm::vec3(-103 * scale_x, -0.5f, i), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		CreateObject("stragan", glm::vec3(-103 * scale_x, -0.5f, i + 1), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		CreateObject("stragan", glm::vec3(-90 * scale_x, -0.5f, i), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 0.0f, 1.0f));
		CreateObject("stragan", glm::vec3(-90 * scale_x, -0.5f, i + 1), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 0.0f, 1.0f));
	}

}

void Create_objects::CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader)
{
	modelTemplates.push_back(std::make_shared<ModelTemplate>(path, name, shader));
}

void Create_objects::CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color)
{
	std::shared_ptr<ModelTemplate> temp = FindTemplate(name);
	if (temp == nullptr)
	{
		std::cout << "Error: Object not created" << std::endl;
		return;
	}
	else
		this->objects.push_back(Model(temp, position, scale, rotate, angle, color));
}
std::shared_ptr<ModelTemplate> Create_objects::FindTemplate(std::string name)
{
	for (auto temp : this->modelTemplates)
		if (name == temp->GetName()) return temp;
	std::cout << "Error: Template not found" << std::endl;
	return nullptr;
}