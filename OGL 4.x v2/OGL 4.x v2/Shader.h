#ifndef SHADER_H
#define SHADER_H

#include "GL\glew.h"
#include "GL\wglew.h"

class Shader
{
public:
	Shader();
	~Shader();

	void Bind();
	void UnBind();
	GLint GetUniform(char* _str);
	void SetGlUniform4f(GLint _uniform, float _xr, float _yg, float _zb, float _wa);

private:
	GLint vertexShader;
	GLint fragmentShader;
	GLint geometryShader;

	GLint shaderProgram;
};

#endif