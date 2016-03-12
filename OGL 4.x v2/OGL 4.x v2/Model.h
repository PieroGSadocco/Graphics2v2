#ifndef MODEL_H
#define MODEL_H

#include "Loader.h"
#include "MeshOGL.h"

#include "Shader.h"
#include "Matrix.h"
#include "Texture.h"

class Model
{
public:
	Model(std::string _path);
	~Model();
	void Draw();

	unsigned int numMeshes;

	Shader* shader;
	Texture* diffuse;
	Texture* normalMap;
	Matrix objectMatrix;
private:
	Model() {};

	MeshOGL* meshesOGL;
};

#endif