#include "init_castle.h"

InitCastle::InitCastle(std::shared_ptr<ShaderProgram> shader)
{
	CreateTemplate("data/cube.obj", "cube", shader);
	CreateTemplate("data/cube_2.obj", "cube_2", shader);
	CreateTemplate("data/medieval-house-textured.obj", "house", shader);
	CreateTemplate("data/mur.obj", "mur", shader);
	CreateTemplate("data/stragan.obj", "stragan", shader);
	CreateTemplate("data/Castle/Castle OBJ.obj", "castle", shader);
	CreateTemplate("data/flaga.obj", "flaga", shader);
	CreateTemplate("data/dym.obj", "dym", shader);
	CreateTemplate("data/pochodnia.obj", "pochodnia", shader);
	CreateTemplate("data/studnia.obj", "studnia", shader);


	// ty
	scale_x = 0.03;
	scale_y = 0.03;
	scale_z = 0.03;
	for (int i = 0; i < 100; i++)
	{
		CreateObject("dym", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(1.0f, 0.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
	}
	scale_x = 0.1;
	scale_y = 0.2;
	scale_z = 0.1;	//podloga
	CreateObject("studnia", glm::vec3(110 * scale_x, 0.0f, 0.0f), glm::vec3(scale_x*5, scale_y*3, scale_z*5), glm::vec3(0.0f, 1.0f, 0.0f), PI/2, glm::vec3(1.0f, 0.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
	CreateSources(glm::vec3(110 * scale_x-0.5, 2.3f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f));
	CreateSources(glm::vec3(110 * scale_x - 0.7, 2.3f, -0.3f), glm::vec3(0.8f, 0.8f, 0.8f));

	CreateSources(glm::vec3(146 * scale_x, 7, -130 * scale_z), glm::vec3(0.8f, 0.8f, 0.8f));
	CreateSources(glm::vec3(146 * scale_x, 7, 203 * scale_z), glm::vec3(0.8f, 0.8f, 0.8f));
	CreateSources(glm::vec3(-167 * scale_x, 7, 203 * scale_z), glm::vec3(0.8f, 0.8f, 0.8f));
	CreateSources(glm::vec3(-167 * scale_x, 7, -130 * scale_z), glm::vec3(0.8f, 0.8f, 0.8f));

	CreateObject("flaga", glm::vec3(-165 * scale_x, 8, -127 * scale_z), glm::vec3(scale_x * 4, scale_y * 4, scale_z * 4), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
	CreateObject("flaga", glm::vec3(-165 * scale_x, 8, 205 * scale_z), glm::vec3(scale_x * 4, scale_y * 4, scale_z * 4), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
	CreateObject("flaga", glm::vec3(145 * scale_x, 8, 205 * scale_z), glm::vec3(scale_x * 4, scale_y * 4, scale_z * 4), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
	CreateObject("flaga", glm::vec3(145 * scale_x, 8, -127 * scale_z), glm::vec3(scale_x * 4, scale_y * 4, scale_z * 4), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.8f, 0.8f, 0.8f));
	
	CreateObject("cube_2", glm::vec3(-10 * scale_x, -0.45f, 40 * scale_z), glm::vec3(150 * scale_x, 0.1, 160 * scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f),0, glm::vec3(0.0f, 0.0f, 0.0f));
	
	for(int i = -5; i < 0; i++)
	CreateObject("house", glm::vec3(12.4 + 3*i, -0.45f,17.0f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f), 1, glm::vec3(1.0f, 0.5f, 0.25f));
	CreateObject("castle", glm::vec3(0.0f, -0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f));
	//mury

	CreateObject("pochodnia", glm::vec3(-158 * scale_x, 0.5f, 140 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 1, glm::vec3(1.0f, 0.5f, 0.0f));
	CreateObject("pochodnia", glm::vec3(-158 * scale_x, 0.5f, -20 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 1, glm::vec3(1.0f, 0.5f, 0.0f));
	
	
	CreateObject("mur", glm::vec3(140 * scale_x, 0.0f, 40 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));                                //0.0f, 0.0f, 0.0f
	CreateObject("mur", glm::vec3(0.0f, 0.0f, -120 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));                                //-1.0f, 0.0f, 13.5f
	CreateObject("mur", glm::vec3(-160 * scale_x, 0.0f, 40 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));                           //13.5f, 0.0f, 14.5f
	CreateObject("mur", glm::vec3(-20 * scale_x, 0.0f, 200 * scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI * 3 / 2, glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));                    //14.5f, 0.0f, 1.0f

	//stragany
	scale_x = 0.2;
	scale_y = 0.6;
	scale_z = 0.2;
	n = 1;
	for (int i = 0; i < 15; i += 3)
	{
		CreateObject("stragan", glm::vec3(-75 * scale_x, -0.5f, i), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f),0, glm::vec3(0.0f, 0.0f, 0.0f));	
		CreateObject("stragan", glm::vec3(-75 * scale_x, -0.5f, i+1), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
		CreateObject("stragan", glm::vec3(-60 * scale_x, -0.5f, i), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 0.0f, 1.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
		CreateObject("stragan", glm::vec3(-60 * scale_x, -0.5f, i+1), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 0.0f, 1.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f));
	}

	
	CreateSources(glm::vec3(-103 * scale_x, 1.5f, 5), glm::vec3(1.0f, 1.0f, 1.0f));
}

void InitCastle::CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader)
{
	_modelTemplates.push_back(std::make_shared<ModelTemplate>(path, name, shader));
}

void InitCastle::CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color, bool is_source, glm::vec3 light_color)
{
	std::shared_ptr<ModelTemplate> temp = FindTemplate(name);
	if (temp == nullptr)
	{
		std::cout << "Error: Object not created" << std::endl;
		return;
	}
	else
		this->_objects.push_back(Model(temp, position, scale, rotate, angle, color));
	if(is_source)
		CreateSources(position+glm::vec3(0.0f, 0.5f, 0.0f), light_color);
}
std::shared_ptr<ModelTemplate> InitCastle::FindTemplate(std::string name)
{
	for (auto temp : this->_modelTemplates)
		if (name == temp->GetName()) return temp;
	std::cout << "Error: Template not found" << std::endl;
	return nullptr;
}

std::unique_ptr<Model> InitCastle::LoadPlayer()
{
	return std::make_unique<Model>(FindTemplate("cube"), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 1.0f));
}

std::vector<std::shared_ptr<ModelTemplate>> InitCastle::LoadTemplates()
{

	return this->_modelTemplates;
}

std::vector<Model> InitCastle::LoadObjects()
{

	return this->_objects;
}

std::vector<Light> InitCastle::LoadLights()
{

	return _lights;
}

std::shared_ptr<Skybox> InitCastle::LoadSkybox(std::shared_ptr<ShaderProgram> shader)
{
	return std::make_shared<Skybox>("data/skybox", shader);
}

void InitCastle::CreateSources(glm::vec3 pos, glm::vec3 col)
{
	Light a;
	a.color = col;
	a.pos = pos;
	_lights.push_back(a);
	//sources[n++] = a;
}
