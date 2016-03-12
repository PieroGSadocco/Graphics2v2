#include "Light.h"

Light::Light()
{

}

Light::~Light()
{

}

void Light::Bind(GLint _shaderMatrixUniform)
{
	glUniformMatrix4fv(_shaderMatrixUniform, 1, GL_FALSE, glm::value_ptr(positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4));
}

void Light::SetPositionXYZ(float _x, float _y, float _z)
{
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[0].x = _x;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[0].y = _y;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[0].z = _z;
}

void Light::SetOrientationXYZ(float _x, float _y, float _z)
{
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[1].x = _x;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[1].y = _y;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[1].z = _z;
}

void Light::SetColorRGB(float _r, float _g, float _b)
{
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[2].x = _r;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[2].y = _g;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[2].z = _b;
}

void Light::SetCameraPositionXYZ(float _x, float _y, float _z)
{
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[3].x = _x;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[3].y = _y;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[3].z = _z;
}

void Light::Float4(float _x, float _y, float _z, float _w)
{
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[0].w = _x;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[1].w = _y;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[2].w = _z;
	positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4[3].w = _w;
}