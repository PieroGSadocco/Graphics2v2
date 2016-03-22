#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(float _r, float _g, float _b);
	~AmbientLight();

	void Bind(GLint _shaderMatrixUniform);

	void SetColorRGB(float _r, float _g, float _b);

private:
	glm::vec3 data;
};

#endif