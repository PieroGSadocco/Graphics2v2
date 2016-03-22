#include "Matrix.h"

Matrix::Matrix()
{
	mat = glm::mat4();
}

Matrix::~Matrix()
{

}

void Matrix::Translate(float _x, float _y, float _z)
{
	mat = glm::translate(mat, glm::vec3(_x, _y, _z));
}

void Matrix::Rotate(float _angle, float _x, float _y, float _z)
{
	mat = glm::rotate(mat, _angle, glm::vec3(_x, _y, _z));
}

void Matrix::Scale(float _x, float _y, float _z)
{
	mat = glm::scale(mat, glm::vec3(_x, _y, _z));
}

void Matrix::Multiply(glm::mat4x4 _this, glm::mat4x4 _by)
{
	mat = _this * _by;
}

void Matrix::Multiply(glm::mat4x4 _this, glm::quat _by)
{
	mat = glm::mat4_cast(_by) * _this;
}

void Matrix::Bind(GLint _shaderMatrixUniform)
{
	glUniformMatrix4fv(_shaderMatrixUniform, 1, GL_FALSE, glm::value_ptr(mat));
}

void Matrix::SetProjection(float _angle, float _width, float _height, float _nearView, float _farView)
{
	mat = glm::perspective(_angle, _width / _height, _nearView, _farView);
}

glm::mat4 Matrix::GetMatrix()
{
	return mat;
}