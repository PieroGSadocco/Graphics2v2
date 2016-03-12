#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

//Directional Light 7f
//->XYZorientation
//->RGBcolor
//->Fintensity

/*		[0]			[1]			[2]			[3]		
x		pX			pY			pZ			iF		
y		cR			cG			cB			?	  */

class DirectionalLight
{
public:
	DirectionalLight();
	~DirectionalLight();

	void Bind(GLint _shaderMatrixUniform);

	void SetOrientationXYZ(float _x, float _y, float _z);
	void SetColorRGB(float _r, float _g, float _b);
	void SetIntensityF(float _f);

private:
	glm::mat4x2 data;
};



#endif