#include "PointLight.h"

PointLight::PointLight()
{

}

PointLight::~PointLight()
{

}

void PointLight::Bind(GLint _shaderMatrixUniform)
{
	glUniformMatrix3fv(_shaderMatrixUniform, 1, GL_FALSE, glm::value_ptr(data));
}

void PointLight::SetPositionXYZ(float _x, float _y, float _z)
{
	data[0].x = _x;
	data[0].y = _y;
	data[0].z = _z;
}

void PointLight::SetColorRGB(float _r, float _g, float _b)
{
	data[1].x = _r;
	data[1].y = _g;
	data[1].z = _b;
}

void PointLight::SetConstantF(float _f)
{
	data[2].x = _f;
}

void PointLight::SetLinearF(float _f)
{
	data[2].y = _f;
}

void PointLight::SetQuadraticF(float _f)
{
	data[2].z = _f;
}
