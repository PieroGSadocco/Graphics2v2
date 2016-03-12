#ifndef LIGHT_H
#define LIGHT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

class Light
{
public:
	Light();
	~Light();

	void Bind(GLint _shaderMatrixUniform);

	void SetPositionXYZ(float _x, float _y, float _z);
	void SetOrientationXYZ(float _x, float _y, float _z);
	void SetColorRGB(float _r, float _g, float _b);
	void SetCameraPositionXYZ(float _x, float _y, float _z);
	void Float4(float _x, float _y, float _z, float _w);

private:
	//Spot Light 11f
	//->XYZposition
	//->RGBcolor
	//->RGBorientation
	//->Fintensity
	//->radius

	//Ambient Light 4f
	//->RGBcolor

/*		[0]			[1]			[2]			[3]		
x		0x			1x			2x			3x		
y		0y			1y			2y			3y		
z		0z			1z			2z			3z		
w		0w			1w			2w			3w	  */

	//shininess
	//constant
	//linear
	//quadratic

	glm::mat4 positionXYZ_orientationXYZ_colorRGB_cameraPosXYZ_float4;

};

#endif