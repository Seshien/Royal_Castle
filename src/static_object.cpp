#include "static_object.h"

using namespace std;
static_object::static_object(std::string path, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate)
	:path(path), position(position), scale(scale), rotate(rotate)
{
	
}
static_object::static_object() {}
void static_object::load_model( )
{
    // Wczytuje zawartoœæ pliku pod œcie¿k¹ "path" i generuje obiekt typu Model.
    // fstream plik;
    ifstream  plik(path);

    if (!plik.good())
    {
        std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
        exit(1);
    }

    vector<float> v, vt, vn;
    string s;
    float wierzcholek;

    while (!plik.eof()) {
        plik >> s;
        if (plik.eof()) break;
        if (s == "#" || s == "o" || s == "usemtl" || s == "s")
        {
            getline(plik, s);
        }
        else if (s == "mtllib")
        {
            getline(plik, s);
        }
        else if (s == "v")
        {
            for (int i = 0; i < 3; i++)
            {
                plik >> wierzcholek;
                if (i == 1 && wierzcholek > wierzcholki[0]) wierzcholki[0] = wierzcholek;
                else if (i == 2 && wierzcholek > wierzcholki[1]) wierzcholki[1] = wierzcholek;
                else if (i == 3 && wierzcholek > wierzcholki[2]) wierzcholki[2] = wierzcholek;
                else if (i == 1 && wierzcholek < wierzcholki[3]) wierzcholki[3] = wierzcholek;
                else if (i == 2 && wierzcholek < wierzcholki[4]) wierzcholki[4] = wierzcholek;
                else if (i == 3 && wierzcholek < wierzcholki[5]) wierzcholki[5] = wierzcholek;
                v.push_back(wierzcholek);
            }
        }
        else if (s == "vt")
        {
            for (int i = 0; i < 2; i++)
            {
                plik >> wierzcholek;
                vt.push_back(wierzcholek);
            }
        }
        else if (s == "vn")
        {
            for (int i = 0; i < 3; i++)
            {
                plik >> wierzcholek;
                vn.push_back(wierzcholek);
            }
        }
        else if (s == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                //wierzcholek
                getline(plik, s, '/');
                int x = stoi(s) - 1;
                vertices.push_back(v[x * 3]);
                vertices.push_back(v[x * 3 + 1]);
                vertices.push_back(v[x * 3 + 2]);
                vertices.push_back(1);

                //tekstura
                getline(plik, s, '/');
                x = stoi(s) - 1;
                texCoords.push_back(vt[x * 2]);
                texCoords.push_back(vt[x * 2 + 1]);

                //normalna
                plik >> s;
                x = stoi(s) - 1;
                vertexNormals.push_back(vn[x * 3]);
                vertexNormals.push_back(vn[x * 3 + 1]);
                vertexNormals.push_back(vn[x * 3 + 2]);
                vertexNormals.push_back(0);
            }
        }
        else {
            cout << "Nie rozpoznano znaku: " << s << endl;
        }
    }
    create_cuboid();
   
}

void static_object::create_object()
{
	glm::mat4 M = glm::mat4(1.0f);
	//glm::mat4 M1 = glm::rotate(M, 1, rotacja);
  
	glm::mat4 M2 = glm::scale(M, scale);
    Mat = glm::translate(M2, position);
  //  glm::mat4 M3 = glm::rotate(M2, rotate);
	
	load_model();
    change_cuboid();
	for (int i = 0; i < 2; i++)
	{
		std::cout << wierzcholki[i] << " " << wierzcholki[i + 1] << " " << wierzcholki[i + 2] << std::endl;
	}
}
bool static_object::collision(glm::vec3 polozenie)
{
    //std::cout << "min x: " << wierzcholki[3] << "   x: " << polozenie.x << " max x: " << wierzcholki[0] << std::endl;
   // std::cout << "min y: " << wierzcholki[4] << "   y: " << polozenie.y << " max y: " << wierzcholki[1] << std::endl;
  //  std::cout << "min z: " << wierzcholki[5] << "   z: " << polozenie.z << " max z: " << wierzcholki[2] << std::endl;
    //std::cout << std::endl;
    if (polozenie.x <= wierzcholki[0] && //x <= max x
        wierzcholki[3] <= polozenie.x && //x >= min x
        polozenie.y <= wierzcholki[1] && //y <= max y
        wierzcholki[4] <= polozenie.y && // y >= mn y
        polozenie.z <= wierzcholki[2] && // z <= max z
        wierzcholki[5] <= polozenie.x) return 1; // z >= min z
    return 0;
}
