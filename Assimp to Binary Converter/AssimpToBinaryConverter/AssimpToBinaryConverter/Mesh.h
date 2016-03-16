#ifndef MESH_H
#define MESH_H

#include "GL\glew.h"
#include "GL\wglew.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <string>
#include <vector>

class Mesh
{
public:
	struct VertexStruct
	{
		float px, py, pz;
		float u, v;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};

	struct TextureStruct
	{
		GLuint id;
		std::string type;
	};

	std::vector<float> vertices;
	std::vector<GLuint> indices;
	std::vector<TextureStruct> textures;

	unsigned int pos;
	unsigned int uv;
	unsigned int normal;
	unsigned int tangent;
	unsigned int biTangent;

	Mesh(std::vector<float> _vertices, std::vector<GLuint> _indices, std::vector<TextureStruct> _textures, unsigned int _pos, unsigned int _uv, unsigned int _normal, unsigned int _tangent, unsigned int _bitangent);
	~Mesh();

private:
};
#endif