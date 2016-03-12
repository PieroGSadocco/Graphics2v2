#ifndef MATRIX_H
#define MATRIX_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

class Matrix
{
public:
	Matrix();
	~Matrix();

	void Translate(float _x, float _y, float _z);
	void Rotate(float _angle, float _x, float _y, float _z);
	void Scale(float _x, float _y, float _z);

	void Multiply(glm::mat4x4 _this, glm::mat4x4 _by);
	void Multiply(glm::mat4x4 _this, glm::quat _by);

	void Bind(GLint _shaderMatrixUniform);

	void SetProjection(float _angle, float _width, float _height, float _nearView, float _farView);

	glm::mat4 GetMatrix();

private:
	glm::mat4 mat;
};

#endif