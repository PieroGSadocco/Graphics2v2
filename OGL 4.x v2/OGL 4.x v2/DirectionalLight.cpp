#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(float _oriX, float _oriY, float _oriZ, float _colR, float _colG, float _colB)
{
	data[0].x = _oriX;
	data[1].x = _oriY;
	data[2].x = _oriZ;

	data[0].y = _colR;
	data[1].y = _colG;
	data[2].y = _colB;
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


