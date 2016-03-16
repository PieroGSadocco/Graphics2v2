#include "Shader.h"

#include "Logger.h"

Shader::Shader(std::string _vertexShaderPath, std::string _geometryShaderPath, std::string _fragmentShaderPath)
{
	vertexShader = 0;
	fragmentShader = 0;
	geometryShader = 0;

	std::string shaderSourceVertex = "";
	std::string shaderSourceGeometry = "";
	std::string shaderSourceFragment = "";

	Loader loader;
	loader.LoadTxt(_vertexShaderPath, shaderSourceVertex);
	loader.LoadTxt(_geometryShaderPath, shaderSourceGeometry);
	loader.LoadTxt(_fragmentShaderPath, shaderSourceFragment);

	BuildAndCompileShader(shaderSourceVertex, shaderSourceGeometry, shaderSourceFragment);
}

Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

void Shader::Bind()
{
	glUseProgram(shaderProgram);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

GLint Shader::GetUniform(char* _str)
{
	return glGetUniformLocation(shaderProgram, _str);
}

void Shader::SetGlUniform4f(GLint _uniform, float _xr, float _yg, float _zb, float _wa)
{
	glUniform4f(_uniform, _xr, _yg, _zb, _wa);
}


void Shader::BuildAndCompileShader(std::string& _vertexShaderSource, std::string& _geometryShaderSource, std::string& _fragmentShaderSource)
{
	const char* shaderStr;

	GLint success;
	GLchar infoLog[512];

	// Vertex shader
	if (_vertexShaderSource != "")
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		shaderStr = _vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, &shaderStr, NULL);
		glCompileShader(vertexShader);

		// Check for compile time errors
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			_vertexShaderSource = "";
		}
	}

	// Geometry shader
	if (_geometryShaderSource != "")
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		shaderStr = _geometryShaderSource.c_str();
		glShaderSource(geometryShader, 1, &shaderStr, NULL);
		glCompileShader(geometryShader);

		// Check for compile time errors
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
			_geometryShaderSource = "";
		}
	}

	// Fragment shader
	if (_fragmentShaderSource != "")
	{
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderStr = _fragmentShaderSource.c_str();
		glShaderSource(fragmentShader, 1, &shaderStr, NULL);
		glCompileShader(fragmentShader);

		// Check for compile time errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			_fragmentShaderSource = "";
		}
	}

	// Link shaders
	shaderProgram = glCreateProgram();

	if (_vertexShaderSource != "")
		glAttachShader(shaderProgram, vertexShader);
	if (_geometryShaderSource != "")
		glAttachShader(shaderProgram, geometryShader);
	if (_fragmentShaderSource != "")
		glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	Logger::Log("Shaders Loaded/Compiled SUCCESS\n");
}