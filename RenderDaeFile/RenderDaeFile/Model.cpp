#include "Model.h"
#include "glm/vec3.hpp"

using namespace std;

void Model::loadModel(string path) {

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs/* | aiProcess_JoinIdenticalVertices*/);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
	
}

void Model::drawWire() {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].drawWire();
}

void Model::drawSolid() {
	
	//printf("mesh count : %d\n", meshes.size());
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].drawSolid();
}

void Model::processNode(aiNode* node, const aiScene* scene) {

	// ���� ��带 ó���ϰ�
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
		// processMesh�� �Է¹��� aiMesh�� mesh ��ü�� ��ȯ�Ѵ�.
	}

	// �� �������� �ڽ��� ó���Ѵ�. (preOrder ���)
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
	
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	vector <glm::vec3> vertices;
	vector <unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		
		vertices.push_back(vector); 
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace * face = &mesh->mFaces[i];
		for (unsigned int j = 0; j < face->mNumIndices; j++)
			indices.push_back(face->mIndices[j]);
	}

	return Mesh(vertices, indices);

}
