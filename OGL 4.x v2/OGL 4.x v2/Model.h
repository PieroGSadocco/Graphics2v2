#ifndef MODEL_H
#define MODEL_H

#include "Loader.h"
#include "MeshOGL.h"

#include "Matrix.h"
#include "Camera.h"

#include "Texture.h"

class Shader;

class Model
{
public:
	Model(std::string _path);
	~Model();
	void Draw(Matrix* mat, Camera* cam);

	unsigned int numMeshes;

	Shader* shader;
	Texture* diffuse;
	Texture* normalMap;
	Texture* renderedMap;
	Matrix objectMatrix;
private:
	Model() {};

	MeshOGL* meshesOGL;
};

#endif