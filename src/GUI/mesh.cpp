#include "mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{

    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    initMesh();
	findMinMax();

}

void Mesh::initMesh()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::findMinMax()
{
	bool first = true;
	for (auto vert : vertices)
	{
		glm::vec3 pos = vert.Position;
		if (first)
		{
			min = pos;
			max = pos;
			first = false;
		}
		//Chcemy znalezc dwa najbardziej wystajace punkty modelu
		if (min.x > pos.x) min.x = pos.x; 
		if (min.y > pos.y) min.y = pos.y;
		if (min.z > pos.z) min.z = pos.z;
		if (max.x < pos.x) max.x = pos.x;
		if (max.y < pos.y) max.y = pos.y;
		if (max.z < pos.z) max.z = pos.z;
	}

}

void Mesh::drawSolid(std::shared_ptr<ShaderProgram> shader)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Draw(shader);
}

void Mesh::drawWire(std::shared_ptr<ShaderProgram> shader)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Draw(shader);
}

bool Mesh::Collision(glm::vec3 pos, glm::mat4 mat)
{
	glm::vec4 max_t = mat * glm::vec4(max.x, max.y, max.z, 1.0f);
	glm::vec4 min_t = mat * glm::vec4(min.x, min.y, min.z, 1.0f);

	if (max_t.x < min_t.x) std::swap(max_t.x, min_t.x);
	if (max_t.y < min_t.y) std::swap(max_t.y, min_t.y);
	if (max_t.z < min_t.z) std::swap(max_t.z, min_t.z);

	if (pos.x <= max_t.x && //x <= max x
		min_t.x <= pos.x && //x >= min x
		pos.y <= max_t.y && //y <= max y
		min_t.y <= pos.y && // y >= mn y
		pos.z <= max_t.z && // z <= max z
		min_t.z <= pos.z) // z >= min z
	{
		printf("Collision test: max  %f %f %f, min %f %f %f \n ", max_t.x, max_t.y, max_t.z, min_t.x, min_t.y, min_t.z);
		return true; 
	}
	return false;
}


void Mesh::Draw(std::shared_ptr<ShaderProgram> shader)
{

    glActiveTexture(GL_TEXTURE0); 
	glUniform1i(shader->u("TEX"), 0);
	glBindTexture(GL_TEXTURE_2D, textures[0].id);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}