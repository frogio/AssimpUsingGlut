#include "mesh.h"

using namespace std;

Mesh::Mesh(vector<Vertex *> _vertices, vector<unsigned int> _indices, vector<Texture> _textures) {
	vertices = _vertices;			// ���ؽ� ����
	indices = _indices;				// ���ؽ� �׸��� ����
	textures = _textures;
	normal = CalculFaceNormal();	// ��� ��鿡 ���� �븻����
}

void Mesh::drawWire() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	
	for (unsigned int i = 0; i < indices.size() - 2/* �޸� ����� ���� ���ϵ��� -2������ �׸����� �Ѵ�. */; i += 3/* 3���� ��� ���� �׸��� +3�� ���ش�*/) {		
		glBegin(GL_LINES);

		for (int j = 0; j < 3; j++){
			// j : 0 start = i + 0, end = i + 1
			// j : 1 start = i + 1, end = i + 2
			// j : 2 start = i + 2, end = i + 0
			int start = indices[i + j % 3];
			int end = indices[i + (j + 1) % 3];
			glVertex3f(vertices[start]->Position.x, vertices[start]->Position.y, vertices[start]->Position.z);
			glVertex3f(vertices[end]->Position.x, vertices[end]->Position.y, vertices[end]->Position.z);
		}

		glEnd();
	}
	glEnable(GL_LIGHTING);
	//
	glPopMatrix();
}

void Mesh::drawSolid() {

	printf("vertex count : %d\n", vertices.size());
	glPushMatrix();

	for (unsigned int i = 0; i < vertices.size() - 2/* �޸� ����� ���� ���ϵ��� -2������ �׸����� �Ѵ�. */; i += 3/* 3���� ��� ���� �׸��� +3�� ���ش�*/) {
		glBegin(GL_POLYGON);
		glNormal3f(normal[i / 3]->x, normal[i / 3]->y, normal[i / 3]->z);
		// ��鿡 ���� �븻���ʹ� ���ؽ��� 3���� ��� �����ϹǷ� / 3�� ���ش�.

		for (int j = 0; j < 3; j++)
			glVertex3f(vertices[indices[i + j]]->Position.x, vertices[indices[i + j]]->Position.y, vertices[indices[i + j]]->Position.z);

		glEnd();
	}

	glPopMatrix();
}


vector<glm::vec3*> Mesh::CalculFaceNormal() {			// ��鿡 ���� �븻���� ���Ѵ�.
	vector<glm::vec3*> result;

	for (unsigned int i = 0; i < vertices.size() - 2/* �޸� ����� ���� ���ϵ��� -2������ �׸����� �Ѵ�. */; i += 3/* 3���� ��� ���� �׸��� +3�� ���ش�*/) {
		
		glm::vec3 v0 = vertices[indices[i + 1]]->Position - vertices[indices[i]]->Position;
		glm::vec3 v1 = vertices[indices[i + 2]]->Position - vertices[indices[i]]->Position;

		glm::vec3* normal = new glm::vec3();
		*normal = glm::normalize(glm::cross(v0, v1));

		result.push_back(normal);
	}

	return result;
}