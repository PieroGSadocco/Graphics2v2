#ifndef SHADER_H
#define SHADER_H

#include "GL\glew.h"
#include "GL\wglew.h"

#include <string>

#include "Loader.h"

class Shader
{
public:
	Shader(std::string _vertexShaderPath, std::string _geometryShaderPath, std::string _fragmentShaderPath);
	~Shader();

	void Bind();
	void UnBind();
	GLint GetUniform(char* _str);
	void SetGlUniform4f(GLint _uniform, float _xr, float _yg, float _zb, float _wa);

	GLint GetShaderProgram() { return shaderProgram; };

private:
	GLint vertexShader;
	GLint fragmentShader;
	GLint geometryShader;

	GLint shaderProgram;

	void BuildAndCompileShader(std::string& _vertexShaderPath, std::string& _geometryShaderPath, std::string& _fragmentShaderPath);
};

#endif