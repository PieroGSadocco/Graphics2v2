#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

//Point Light 9f
//->XYZposition
//->RGBcolor
//->Fconstant
//->Flinear
//->Fquadratic

/*		[0]			[1]			[2]	
x		X			R			C	
y		Y			G			L	
z		Z			B			Q	*/

class PointLight
{
public:
	PointLight();
	~PointLight();

	void Bind(GLint _shaderMatrixUniform);

	void SetPositionXYZ(float _x, float _y, float _z);
	void SetColorRGB(float _r, float _g, float _b);
	void SetConstantF(float _f);
	void SetLinearF(float _f);
	void SetQuadraticF(float _f);

private:
	glm::mat3 data;
};

#endif