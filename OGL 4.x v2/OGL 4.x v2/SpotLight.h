#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"


//Spot Light 13f
//->XYZposition
//->RGBcolor
//->XYZorientation
//->Fconstant
//->Flinear
//->Fquadratic
//->FcutOff

/*		[0]			[1]			[2]			[3]
x		X			R			X			Con
y		Y			G			Y			Lin
z		Z			B			Z			Qua

Cut
*/

class SpotLight
{
public:
	SpotLight();
	SpotLight(float _posX, float _posY, float _posZ, float _colR, float _colG, float _colB, float _oriX, float _oriY, float _oriZ, float _constant, float _linear, float _quadratic, float _innerCutOff, float _outerCutOff);
	~SpotLight();

	void Bind(GLint _shaderMatrixUniform1, GLint _shaderMatrixUniform2);

	void SetPositionXYZ(float _x, float _y, float _z);
	void SetColorRGB(float _r, float _g, float _b);
	void SetOrientationXYZ(float _x, float _y, float _z);
	void SetConstantF(float _f);
	void SetLinearF(float _f);
	void SetQuadraticF(float _f);
	void SetCutOffsFF(float _inner,float _outer);

private:
	glm::mat4x3 data;
	glm::vec2 cutOffs;
};

#endif