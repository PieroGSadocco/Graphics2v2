#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::Bind(GLint _shaderMatrixUniform1, GLint _shaderMatrixUniform2)
{
	glUniformMatrix4x3fv(_shaderMatrixUniform1, 1, GL_FALSE, glm::value_ptr(data));
	glUniform2f(_shaderMatrixUniform2, cutOffs.x, cutOffs.y);
}

void SpotLight::SetPositionXYZ(float _x, float _y, float _z)
{
	data[0].x = _x;
	data[0].y = _y;
	data[0].z = _z;
}

void SpotLight::SetColorRGB(float _r, float _g, float _b)
{
	data[1].x = _r;
	data[1].y = _g;
	data[1].z = _b;
}

void SpotLight::SetOrientationXYZ(float _x, float _y, float _z)
{
	data[2].x = _x;
	data[2].y = _y;
	data[2].z = _z;
}

void SpotLight::SetConstantF(float _f)
{
	data[3].x = _f;
}

void SpotLight::SetLinearF(float _f)
{
	data[3].y = _f;
}

void SpotLight::SetQuadraticF(float _f)
{
	data[3].z = _f;
}

void SpotLight::SetCutOffsFF(float _inner, float _outer)
{
	cutOffs.x = glm::cos(glm::radians(_inner));
	cutOffs.y = glm::cos(glm::radians(_outer));
}
