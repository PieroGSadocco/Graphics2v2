#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::SpotLight(float _posX, float _posY, float _posZ, float _colR, float _colG, float _colB, float _oriX, float _oriY, float _oriZ, float _constant, float _linear, float _quadratic, float _innerCutOff, float _outerCutOff)
{
	data[0].x = _posX;
	data[0].y = _posY;
	data[0].z = _posZ;

	data[1].x = _colR;
	data[1].y = _colG;
	data[1].z = _colB;

	data[2].x = _oriX;
	data[2].y = _oriY;
	data[2].z = _oriZ;

	data[3].x = _constant;

	data[3].y = _linear;

	data[3].z = _quadratic;

	cutOffs.x = glm::cos(glm::radians(_innerCutOff));
	cutOffs.y = glm::cos(glm::radians(_outerCutOff));
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
