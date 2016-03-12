#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"

class Object
{
public:
	Object();
	~Object();

	Mesh* mesh;
	Model* model;
	Shader* shader;
	Texture* diffuse;
	Texture* normalMap;
	Matrix objectMatrix;

	void Draw();

private:
};

#endif