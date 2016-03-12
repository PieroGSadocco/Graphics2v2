#ifndef MESH2_H
#define MESH2_H

#include "GL\glew.h"
#include "GL\wglew.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <string>
#include <vector>

#include "Loader.h"

class Mesh2
{
public:
	Mesh2();
	~Mesh2();
	void Draw();

	

private:

	GLuint VAO, VBO, EBO;
};
#endif