#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model
{
public:
	Model() {};
	Model(std::string path){this->loadModel(path);}
	void CreateBinaryFile();

private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::string fileName;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Mesh::TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);


};

#endif