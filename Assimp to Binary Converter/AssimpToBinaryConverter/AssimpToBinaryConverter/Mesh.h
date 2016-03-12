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
		float nx, ny, nz;
		float u, v;
	};

	struct TextureStruct
	{
		GLuint id;
		std::string type;
	};

	std::vector<float> vertices;
	std::vector<GLuint> indices;
	std::vector<TextureStruct> textures;

	int type;

	Mesh(std::vector<float> vertices, std::vector<GLuint> indices, std::vector<TextureStruct> textures, int _type);
	~Mesh();

private:
};
#endif