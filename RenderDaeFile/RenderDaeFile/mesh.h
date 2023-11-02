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
	vector<glm::vec3> vertices;				// 버텍스 집합
	vector<unsigned int> indices;			// 버텍스의 찍는 순서

	glm::vec3 CalculFaceNormal(int idx);

public: 
	Mesh(vector<glm::vec3> _vertices, vector<unsigned int> _indices);
	void drawWire();
	void drawSolid();


};

#endif