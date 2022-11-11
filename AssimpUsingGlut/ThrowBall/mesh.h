#ifndef __MESH_H__
#define __MESH_H__


#include <string>
#include <vector>
#include <unordered_set>
#include "glm/glm/glm.hpp"
#include "gl/glut.h"


using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextCoords;

	bool operator==(const Vertex& v) {
		return this->Position == v.Position;
	}

};

struct Texture {
	unsigned int id;
	string type;
};

class Mesh {
public:
	vector<Vertex *> vertices;				// ���ؽ� ����
	vector<unsigned int> indices;			// ���ؽ��� ��� ����
	//vector<unsigned int> faces;
	vector<Texture> textures;

	Mesh(vector<Vertex *> _vertices, vector<unsigned int> indices, vector<Texture> _textures);
	void drawWire();
	void drawSolid();
	vector<Vertex *> getVertices();


	//~Mesh() {
	//	for (int i = 0; i < vertices.size(); i++)
	//		delete vertices[i];
	//}


};

#endif