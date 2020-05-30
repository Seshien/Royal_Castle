#include "model.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

  
    void Model::create_cuboid()
    {
        cuboid.push_back(wierzcholki[0]);
        cuboid.push_back(wierzcholki[4]);
        cuboid.push_back(wierzcholki[5]);
        cuboid.push_back(wierzcholki[0]);
        cuboid.push_back(wierzcholki[4]);
        cuboid.push_back(wierzcholki[2]);
        cuboid.push_back(wierzcholki[0]);
        cuboid.push_back(wierzcholki[1]);
        cuboid.push_back(wierzcholki[2]);
        cuboid.push_back(wierzcholki[3]);
        cuboid.push_back(wierzcholki[1]);
        cuboid.push_back(wierzcholki[2]);
        cuboid.push_back(wierzcholki[3]);
        cuboid.push_back(wierzcholki[1]);
        cuboid.push_back(wierzcholki[5]);
        cuboid.push_back(wierzcholki[3]);
        cuboid.push_back(wierzcholki[4]);
        cuboid.push_back(wierzcholki[5]);
        cuboid.push_back(wierzcholki[3]);
        cuboid.push_back(wierzcholki[4]);
        cuboid.push_back(wierzcholki[2]);
        cuboid.push_back(wierzcholki[0]);
        cuboid.push_back(wierzcholki[1]);
        cuboid.push_back(wierzcholki[5]);
    }

    void Model::change_cuboid()
    {
        for (int i = 0; i < 2; i++)
        {
            cuboid_ver = glm::vec4((GLfloat)wierzcholki[i*2], (GLfloat)wierzcholki[i*2 + 1], (GLfloat)wierzcholki[i * 2 + 2], 1.0f);
            cuboid_ver = Mat * cuboid_ver;
            wierzcholki[i * 2] = cuboid_ver.x;
            wierzcholki[i * 2 + 1] = cuboid_ver.y;
            wierzcholki[i * 2 + 2] = cuboid_ver.z;
        }
        cuboid.clear();
        create_cuboid();
    }

    void  Model::drawSolid()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices.data());
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals.data());
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords.data());

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 4);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }
