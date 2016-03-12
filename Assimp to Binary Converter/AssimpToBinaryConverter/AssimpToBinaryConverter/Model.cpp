#include "Model.h"

#include "Logger.h"

#include <fstream>


void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string str = "ASSIMP ERROR: \""; str += path; str += "\" NOT LOADED;";
		Logger::Log(str);
		return;
	}
	
	int foundSlash = 0;
	int foundDot = path.size()-1;
	for (int i = 0; i != path.size() - 1; ++i)
	{
		if (path[i] == '/' || path[i] == '\\')
			foundSlash = i+1;

		if (path[i] == '.')
			foundDot = i;
	}

	fileName = "";
	for (int i = foundSlash; i != foundDot; ++i)
	{
		fileName += path[i];
	}

	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);

	std::string str = "Model ASSIMP: \""; str += path; str += "\" LOADED;";
	Logger::Log(str);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	std::vector<float> vertices;
	std::vector<GLuint> indices;
	std::vector<Mesh::TextureStruct> textures;
	int type = 0;

	//find type
	// mesh type
	// 0 = pos,		uv,			normal								pun
	// 1 = pos,		uv												pu
	// 2 = pos,		normal											pn
	// 3 = pos,		uv,			normal,		tangent,	bitangent	puntb
	// 4 = pos,		normal,		tangent,	bitangent				pntb

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Mesh::VertexStruct vertex;

		// Positions
		vertex.px = mesh->mVertices[i].x;
		vertex.py = mesh->mVertices[i].y;
		vertex.pz = mesh->mVertices[i].z;

		// Normals
		vertex.nx = mesh->mNormals[i].x;
		vertex.ny = mesh->mNormals[i].y;
		vertex.nz = mesh->mNormals[i].z;

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			vertex.u = mesh->mTextureCoords[0][i].x;
			vertex.v = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.u = 0.0f;
			vertex.v = 0.0f;
		}

		vertices.push_back(vertex.px);
		vertices.push_back(vertex.py);
		vertices.push_back(vertex.pz);

		vertices.push_back(vertex.nx);
		vertices.push_back(vertex.ny);
		vertices.push_back(vertex.nz);

		vertices.push_back(vertex.u);
		vertices.push_back(vertex.v);
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		std::vector<Mesh::TextureStruct> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		std::vector<Mesh::TextureStruct> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, type);
}

std::vector<Mesh::TextureStruct> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Mesh::TextureStruct> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Mesh::TextureStruct texture;
		//texture.id = TextureFromFile(str.C_Str(), this->directory);
		texture.type = typeName;
		//texture.path = str;
		textures.push_back(texture);
	}
	return textures;
}








struct MeshData
{
	unsigned int dataType;

	unsigned int numData;
	float* data;

	unsigned int numIndices;
	unsigned int* indices;
};

void Model::CreateBinaryFile()
{
	std::string name = fileName; name += ".model";
	std::ofstream file(name, std::ofstream::binary);

	// write num meshes
	unsigned int numMeshes = meshes.size();
	file.write((const char*)&numMeshes, sizeof(numMeshes));

	// for every mesh
	for (int i = 0; i != meshes.size(); ++i)
	{
		unsigned int type = meshes[i].type;
		file.write((const char*)&type, sizeof(type));
		// write mesh type
		// 0 = pos,		uv,			normal								pun
		// 1 = pos,		uv												pu
		// 2 = pos,		normal											pn
		// 3 = pos,		uv,			normal,		tangent,	bitangent	puntb
		// 4 = pos,		normal,		tangent,	bitangent				pntb
		
		// write mesh vertices size
		unsigned int vSize = meshes[i].vertices.size();
		file.write((const char*)&vSize, sizeof(unsigned int));
		
		// write mesh vertices
		file.write((const char*)&meshes[i].vertices[0], sizeof(float) * meshes[i].vertices.size());

		// write mesh indices size
		unsigned int iSize = meshes[i].indices.size();
		file.write((const char*)&iSize, sizeof(unsigned int));
		
		// write mesh indices
		file.write((const char*)&meshes[i].indices[0], sizeof(GLuint) * meshes[i].indices.size());
	}
	file.close();

	// open file
	std::ifstream testFile(name, std::ifstream::binary);
	
	MeshData* mData;
	
	// get num meshes
	unsigned int numMesh;
	testFile.read((char*)&numMesh, sizeof(unsigned int));
	
	//create MeshData
	mData = new MeshData[numMesh];
	
	// for every mesh
	for (unsigned int i = 0; i != numMesh; ++i)
	{
		// get mesh type
		testFile.read((char*)&mData[i].dataType, sizeof(unsigned int));
		
		// get mesh vertices size
		testFile.read((char*)&mData[i].numData, sizeof(unsigned int));
	
		// get mesh vertices
		mData[i].data = new float[mData[i].numData];
		testFile.read((char*)&(*mData[i].data), mData[i].numData * sizeof(float));
	
		// get mesh indices size
		testFile.read((char*)&mData[i].numIndices, sizeof(unsigned int));
		
		// get mesh indices
		mData[i].indices = new unsigned int[mData[i].numIndices];
		testFile.read((char*)&*mData[i].indices, mData[i].numIndices * sizeof(GLuint));
	
	}
}