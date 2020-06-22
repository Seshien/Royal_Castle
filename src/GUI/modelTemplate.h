
// Hello there

#pragma once

#include <iostream>
#include <vector>
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <GLFW\glfw3.h>
#include "..\Dependiences\stb_image.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "shaderprogram.h"
#include "mesh.h"
//#include "constants.h"

unsigned int TextureFromFile(const char* path, const std::string& directory);

class ModelTemplate
{
public:
	//, float angle, glm::vec3 rotate, glm::vec3 color
    ModelTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader)
    {
		this->name = name;
		this->shader = shader;
        loadModel(path);
    }

    void Draw();
	void DrawWire();

    std::vector<Texture> textures_loaded;
	std::vector<Mesh> GetMeshes() { return this->meshes; }
	std::shared_ptr<ShaderProgram> GetShader() { return this->shader; }
	bool Collision(const glm::vec3 pos, const glm::mat4 mat)
	{
		for (auto mesh : meshes)
			if (mesh.Collision(pos, mat)) return true;
		return false;
	}
	std::string GetName() { return this->name; }
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
	std::string name;
	std::shared_ptr<ShaderProgram> shader;
    void loadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};




