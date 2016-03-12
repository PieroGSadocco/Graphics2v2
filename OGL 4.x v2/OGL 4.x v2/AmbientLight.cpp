#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::Bind(GLint _shaderMatrixUniform)
{
	glUniform3f(_shaderMatrixUniform, data.x, data.y, data.z);
}

void AmbientLight::SetColorRGB(float _r, float _g, float _b)
{
	data.x = _r;
	data.y = _g;
	data.z = _b;
}
