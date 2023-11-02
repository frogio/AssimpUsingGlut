#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include <glm/vec3.hpp>

#include "Mesh.h"

using namespace std;

class Model {
public:
	Model(const char* _path) : path(_path){
		loadModel(path);
	}

	void drawWire();
	void drawSolid();
	//~Model() {
	//	for (int i = 0; i < meshes.size(); i++)
	//		delete meshes[i];
	//}

private:
	vector<Mesh> meshes;
	string directory;
	const char * path;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};

#endif