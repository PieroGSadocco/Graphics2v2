#include "Mesh2.h"

Mesh2::Mesh2()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

Mesh2::~Mesh2()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	VAO = 0;
	VBO = 0;
	EBO = 0;
}

void Mesh2::Draw()
{
	
}
