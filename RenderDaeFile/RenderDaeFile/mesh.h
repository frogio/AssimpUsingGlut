#ifndef __MESH_H__
#define __MESH_H__


#include <string>
#include <vector>
#include <unordered_set>
#include "glm/glm.hpp"
#include "gl/glut.h"


using namespace std;

class Mesh {
private:
	vector<glm::vec3> vertices;				// ���ؽ� ����
	vector<unsigned int> indices;			// ���ؽ��� ��� ����

	glm::vec3 CalculFaceNormal(int idx);

public: 
	Mesh(vector<glm::vec3> _vertices, vector<unsigned int> _indices);
	void drawWire();
	void drawSolid();


};

#endif