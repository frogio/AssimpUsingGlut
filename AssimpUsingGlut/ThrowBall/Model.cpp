#include "Model.h"



using namespace std;

void Model::loadModel(string path) {


	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs/* | aiProcess_JoinIdenticalVertices*/);

	//const aiScene* scene = importer.ReadFile(path,NULL);


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
	
	printf("mesh count : %d\n", meshes.size());
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].drawSolid();
	
	/*
	for (int t = 0; t < meshes[0].; ++t) {
		const aiFace* face = &meshes.mFaces[t];
		GLenum face_mode;

		glBegin(GL_POLYGON);

		for (int i = 0; i < face->mNumIndices; i++) {
			int index = face->mIndices[i];
			if (mesh->mNormals != NULL) {
				glNormal3fv(&mesh->mNormals[index].x);

			}
			glVertex3fv(&mesh->mVertices[index].x);
		}

		glEnd();
	}
	*/
}

void Model::processNode(aiNode* node, const aiScene* scene) {

	// 현재 노드를 처리하고
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
		// processMesh로 입력받은 aiMesh를 mesh 객체로 변환한다.
	}

	// 그 다음으로 자식을 처리한다. (preOrder 방식)
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
	
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	vector <Vertex *> vertices;
	vector <unsigned int> indices;
	vector <Texture> textures;
	/*
	glm::vec3 minBound, maxBound;

	minBound.x = DBL_MAX;
	minBound.y = DBL_MAX;
	minBound.z = DBL_MAX;

	maxBound.x = DBL_MIN;
	maxBound.y = DBL_MIN;
	maxBound.z = DBL_MIN;
	*/
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		// vertex의 위치, 노말 그리고 텍스쳐 좌표 처리
		// 위치 처리
		Vertex  *vertex = new Vertex();
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		
		vertex->Position = vector;
		/*
		if (minBound.x > vector.x)
			minBound.x = vector.x;
		
		if (minBound.y > vector.y)
			minBound.y = vector.y;
		
		if (minBound.z > vector.z)
			minBound.z = vector.z;
		
		if (maxBound.x < vector.x)
			maxBound.x = vector.x;
		
		if (maxBound.y < vector.y)
			maxBound.y = vector.y;
		
		if (maxBound.z < vector.z)
			maxBound.z = vector.z;

		*/
		// 버텍스 노말 처리
		if(mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex->Normal = vector;
		}

		if (mesh->mTextureCoords[0]) {			// 첫번째 텍스쳐 좌표만 처리
			// mesh가 texture 좌표를 포함하는가?
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex->TextCoords = vec;
		}
		else									// 텍스쳐 좌표가 없을 경우
			vertex->TextCoords = glm::vec2(0.f, 0.f);

		//printf("vertex : %f %f %f\n", vertex.Position.x, vertex.Position.y, vertex.Position.z);
		
		//if (find(vertices.begin(), vertices.end(), vertex) != vertices.end())
		//	continue;
		//
		//else { 
		
			vertices.push_back(vertex); //}
	}
	// indices 처리

	//indices = makeIndices(&vertices);
	//printf("indices Size : %d\n", indices.size());
	//
	//for (int i = 0; i < indices.size(); i++) 
	//	 printf("vertex : %f %f %f\n", vertices[indices[i]].Position.x, vertices[indices[i]].Position.y, vertices[indices[i]].Position.z);

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace * face = &mesh->mFaces[i];
		for (unsigned int j = 0; j < face->mNumIndices; j++)
			indices.push_back(face->mIndices[j]);
	}

//	printf("size of indices : %d\n", indices.size());
	/*
	// marterial 처리
	if (mesh->mMaterialIndex >= 0) {
		// mesh가 머티리얼을 갖고 있을 경우
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	*/

	//printf("total count of vertices : %d\n", vertices.size());
	//printf("total count of indices : %d\n", indices.size());

	//moveToCenter(minBound, maxBound, 3.0f, 0);		// Mesh 벡터에 원소를 추가하기도 전에 참조가 되므로 오류 발생.
	
	//moveToCenter(minBound, maxBound, 3.f, vertices);
	return Mesh(vertices, indices, textures);

}



/*
vector<unsigned int> Model::makeIndices(vector<Vertex>* vertices) {

	vector<unsigned int> indices;
	FILE* fp = fopen(path, "r");
	float pos[3] = {0,};
	char header[256] = { 0, };

	printf("vertices->size : %d\n", vertices->size());

	for (unsigned int i = 0; i < 30; i++) {
		printf("vertex %d : %f %f %f\n", i, (*vertices)[i].Position.x, (*vertices)[i].Position.y, (*vertices)[i].Position.z);
		int idx = 0;

		while (fscanf(fp, "%s %f %f %f", header, &pos[0], &pos[1], &pos[2]) != EOF) {

			if (header[0] == 'v' && header[1] == NULL) {
				Vertex v;
				v.Position.x = pos[0];
				v.Position.y = pos[1];
				v.Position.z = pos[2];


				if ((*vertices)[i] == v){
					printf("searching vertex : %f %f %f\n", v.Position.x, v.Position.y, v.Position.z);
					indices.push_back(idx + 1);
					break;
				}
				idx++;
			}
		}
		rewind(fp);

	}

	for (int i = 0; i < indices.size(); i++) {
		printf("indices : %d\n", indices[i]);
	}

	fclose(fp);
	return indices;
}
*/
/*
vector<Texture> Model:: loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
	
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		Texture texture;
		texture.id = TextureFromFile(str.C_Str, directory);
	
	}
}

unsigned int Model::TextureFromFile(const char* path, const string& directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

*/
void Model::moveToCenter(glm::vec3 minBound, glm::vec3 maxBound, float scale, vector<Vertex*> vertices){

	double longestLength = fmaxf(
		fmaxf(
			fabs(maxBound.x - minBound.x),
			fabs(maxBound.y - minBound.y)
		),
		fabs(maxBound.z - minBound.z)
	);
	
	printf("maxBound : %f %f %f , minBound : %f %f %f\n", maxBound.x, maxBound.y, maxBound.z, minBound.x, minBound.y, minBound.z);

	glm::vec3 center = (maxBound + minBound) / 2.0f;
	glm::vec3 origin(0.0, 0.0, 0.0);

	for (int i = 0; i < vertices.size(); i++) {
		glm::vec3 pos = vertices[i]->Position;
		glm::vec3 vecVertexFromCenter = pos - center;
		
		vecVertexFromCenter /= longestLength;
		vecVertexFromCenter *= scale;
		pos = origin;
		pos += vecVertexFromCenter;
		vertices[i]->Position = pos;
		//printf("idx %d] %f %f %f\n",i, vertices[i]->Position.x, vertices[i]->Position.y, vertices[i]->Position.z);
	}

}