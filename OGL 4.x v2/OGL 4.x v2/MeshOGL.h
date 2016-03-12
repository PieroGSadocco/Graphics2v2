#ifndef MESH_OGL_H
#define MESH_OGL_H

struct MeshOGL
{
	unsigned int numIndices;
	GLuint VBO, VAO, EBO;
};

#endif