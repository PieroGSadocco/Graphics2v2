#ifndef MESH_H
#define MESH_H

#include "GL\glew.h"
#include "GL\wglew.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <string>
#include <vector>
//*

class Mesh
{
private:

public:
	Mesh();
	Mesh(std::string _path);
	void SetUpData(std::vector<float>& _vertexData, std::vector<unsigned int>& _indexData);
	~Mesh();

	void Bind();
	void UnBind();
	void Draw();

	unsigned int numVertices;
	unsigned int numIndices;
	GLuint VBO, VAO, EBO;
	std::string directory;

private:

};
//*/
struct VertexStruct
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureStruct
{
	GLuint id;
	std::string type;
};
/*

class Mesh
{
public:
	std::vector<VertexStruct> vertices;
	std::vector<GLuint> indices;
	std::vector<TextureStruct> textures;

	Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices, std::vector<TextureStruct> textures);
	void Draw();

private:
	
	GLuint VAO, VBO, EBO;
	
	void setupMesh();
};
*/
#endif