#include "mesh.h"

using namespace std;

Mesh::Mesh(vector<glm::vec3> _vertices, vector<unsigned int> _indices) {
	vertices = _vertices;			// 버텍스 벡터
	indices = _indices;				// 버텍스 그리는 순서
}

void Mesh::drawWire() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	
	for (unsigned int i = 0; i < indices.size()/* 메모리 사이즈를 넘지 못하도록 -2까지만 그리도록 한다. */; i += 3/* 3개씩 묶어서 선을 그리니 +3씩 해준다*/) {		
		glBegin(GL_LINES);

		for (int j = 0; j < 3; j++){
			// j : 0 start = i + 0, end = i + 1
			// j : 1 start = i + 1, end = i + 2
			// j : 2 start = i + 2, end = i + 0
			int start = indices[i + j % 3];
			int end = indices[i + (j + 1) % 3];
			glVertex3f(vertices[start].x, vertices[start].y, vertices[start].z);
			glVertex3f(vertices[end].x, vertices[end].y, vertices[end].z);
		}

		glEnd();
	}
	glEnable(GL_LIGHTING);
	//
	glPopMatrix();
}

void Mesh::drawSolid() {

	glPushMatrix();

	for (unsigned int i = 0; i < indices.size()/* 메모리 사이즈를 넘지 못하도록 -2까지만 그리도록 한다. */; i += 3/* 3개씩 묶어서 면을 그리니 +3씩 해준다*/) {
		glBegin(GL_POLYGON);
		// 평면에 대한 노말벡터는 버텍스를 3개씩 묶어서 설정하므로 / 3을 해준다.
		
		glm::vec3 normal = CalculFaceNormal(i);
		glNormal3f(normal.x, normal.y, normal.z);
		for (int j = 0; j < 3; j++)
			glVertex3f(vertices[indices[i + j]].x, vertices[indices[i + j]].y, vertices[indices[i + j]].z);

		glEnd();
	}

	glPopMatrix();
}


glm::vec3 Mesh::CalculFaceNormal(int idx) {			// 평면에 대한 노말값을 구한다.
		
	glm::vec3 v0 = vertices[indices[idx + 1]] - vertices[indices[idx]];
	glm::vec3 v1 = vertices[indices[idx + 2]] - vertices[indices[idx]];

	return glm::normalize(glm::cross(v0, v1));
}