#include "Mesh.h"

//Mesh::Mesh(std::vector<float> vertices, std::vector<GLuint> indices, std::vector<TextureStruct> textures, int _type)
//{
//	this->vertices = vertices;
//	this->indices = indices;
//	this->textures = textures;
//	this->type = _type;
//}

Mesh::Mesh(std::vector<float> _vertices, std::vector<GLuint> _indices, std::vector<TextureStruct> _textures, 
	unsigned int _pos, unsigned int _uv, unsigned int _normal, unsigned int _tangent, unsigned int _bitangent)
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
	this->pos = _pos;
	this->uv = _uv;
	this->normal = _normal;
	this->tangent = _tangent;
	this->biTangent = _bitangent;
}

Mesh::~Mesh()
{

}

