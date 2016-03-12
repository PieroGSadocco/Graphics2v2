#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<GLuint> indices, std::vector<TextureStruct> textures, int _type)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->type = _type;
}

Mesh::~Mesh()
{

}

