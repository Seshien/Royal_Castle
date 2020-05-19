/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

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
#include "..\GUI\shaderprogram.h"
#include "..\..\mesh.h"
//#include "constants.h"

unsigned int TextureFromFile(const char* path, const std::string& directory);

class ModelWIP
{
public:

    ModelWIP(std::string path, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate)
    {
        loadModel(path);
        glm::mat4 M = glm::mat4(1.0f);
        glm::mat4 M1 = glm::rotate(M, 1.0f, rotate);
        glm::mat4 M2 = glm::scale(M, scale);
        Mat = glm::translate(M2, position);
    }

    void Draw();

    glm::mat4 Mat;
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};




