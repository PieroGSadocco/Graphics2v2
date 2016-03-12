#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::Bind(GLint _shaderMatrixUniform)
{
	glUniformMatrix4x2fv(_shaderMatrixUniform, 1, GL_FALSE, glm::value_ptr(data));
}

void DirectionalLight::SetOrientationXYZ(float _x, float _y, float _z)
{
	data[0].x = _x;
	data[1].x = _y;
	data[2].x = _z;
}

void DirectionalLight::SetColorRGB(float _r, float _g, float _b)
{
	data[0].y = _r;
	data[1].y = _g;
	data[2].y = _b;
}

void DirectionalLight::SetIntensityF(float _f)
{
	data[3].x = _f;
}


