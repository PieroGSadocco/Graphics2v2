#include "Shader.h"


#include <iostream>
#include "Logger.h"

// shader 1
/*
//																																	VERTEX
const GLchar* vertexShaderSource = {
"#version 330 core\n"

"layout(location = 0) in vec4 position;"
"layout(location = 1) in vec4 color;"
"layout(location = 2) in vec2 texCoord;"
"layout(location = 3) in vec3 normal;"
//"layout(location = 4) in vec3 tangent;"
//"layout(location = 5) in vec3 biTangent;"



"out VS_OUT\n"
"{"
"	vec3 color;"
"	vec3 FragPos;"
"	vec3 Normal;"
"	vec2 TexCoord;"
"	vec4 vertexColor;"
"} vs_out;"

"uniform mat4 viewMatrix;"
"uniform mat4 modelMatrix;"

"void main()"
"{"
"	gl_Position = viewMatrix * modelMatrix * position;"

"	vs_out.FragPos = vec3(modelMatrix * vec4(position.xyz, 1.0));"
"	vs_out.Normal = mat3(transpose(inverse(modelMatrix))) * normal;"
"	vs_out.TexCoord = texCoord;"

"	vs_out.vertexColor = color;"
"	vs_out.color = color.rgb;"
"}"};

//																																	GEOMETRY
const GLchar* geometryShaderSource = {
"p"
};

//																																	FRAGMENT
const GLchar* fragmentShaderSource = {
"#version 330 core\n"

"in VS_OUT\n"
"{"
"	vec3 color;"
"	vec3 FragPos;"
"	vec3 Normal;"
"	vec2 TexCoord;"
"	vec4 vertexColor;"
"} fs_in;"

//"in vec3 FragPos;"
//"in vec3 Normal;"
//"in vec2 TexCoord;"

"in vec4 vertexColor;"

"out vec4 color;"

"uniform sampler2D normalMap;"
"uniform sampler2D diffuseMap;"

"uniform vec3 cameraPos;"

"uniform vec3 ambientLight;"
"uniform mat4x2 directionalLight;"
"uniform mat3 pointLight;"
"uniform mat4x3 spotLight;"
"uniform vec2 spotCutOffs;"

"void main()"
"{"
"	vec3 ambient = vec3(0.0, 0.0, 0.0);"
"	vec3 directional = vec3(0.0, 0.0, 0.0);"
"	vec3 point = vec3(0.0, 0.0, 0.0);"
"	vec3 spot = vec3(0.0, 0.0, 0.0);"

"	float materialShininess = 256;"
//												// normal map
"bool normalMapping = true;"
"vec3 normal = normalize(fs_in.Normal);"

"if(normalMapping == true)"
"{"
"normal = texture(normalMap, fs_in.TexCoord).rgb;"
"normal = normalize(normal * 2.0 - 1.0);"

// Skyrim Snow?
//"normal = normalize(normal * normalize(fs_in.Normal));"
"}"



//												// ambient light
"	ambient = ambientLight;"

//												// directional light
//organize data	
"	vec3 directionalOrientation = vec3(directionalLight[0].x, directionalLight[1].x, directionalLight[2].x);"
"	vec3 directionalColor = vec3(directionalLight[0].y, directionalLight[1].y, directionalLight[2].y);"
"	float directionalIntensity = directionalLight[3].x;"

//diffuse
"	vec3 directionalNorm = normalize(normal);"
"	vec3 directionalLightDir = normalize(-directionalOrientation);"
"	float directionalDiff = max(dot(directionalNorm, directionalLightDir), 0.0);"
"	vec3 directionalDiffuse = directionalDiff * directionalColor;"

//specular
"	vec3 directionalViewDir = normalize(cameraPos - fs_in.FragPos);"
"	vec3 directionalReflectDir = reflect(-directionalLightDir, directionalNorm);"
"	float directionalSpec = pow(max(dot(directionalViewDir, directionalReflectDir), 0.0), materialShininess);"
"	vec3 directionalSpecular = directionalSpec * directionalColor;"

"	directional = (directionalDiffuse) + (directionalSpecular);"

//												// point light
//organize data	
"	vec3 pointPosition = vec3(pointLight[0].x, pointLight[0].y, pointLight[0].z);"
"	vec3 pointColor = vec3(pointLight[1].x, pointLight[1].y, pointLight[1].z);"
"	float pointConstant = pointLight[2].x;"
"	float pointLinear = pointLight[2].y;"
"	float pointQuadratic = pointLight[2].z;"

// diffuse
"	vec3 pointNorm = normalize(normal);"
"	vec3 pointLightDir = normalize(pointPosition - fs_in.FragPos);"
"	float pointDiff = max(dot(pointNorm, pointLightDir), 0.0);"
"	vec3 pointDiffuse = pointColor * pointDiff;"

// specular
"	vec3 pointViewDir = normalize(cameraPos - fs_in.FragPos);"
"	vec3 pointReflectDir = reflect(-pointLightDir, pointNorm);"
"	float pointSpec = pow(max(dot(pointViewDir, pointReflectDir), 0.0), materialShininess);"
"	vec3 pointSpecular = pointColor * pointSpec;"

// attenuation
"	float distance = length(pointPosition - fs_in.FragPos)*2;"
"	float attenuation = 1.0f / (pointConstant + pointLinear * distance + pointQuadratic * (distance * distance));"

"	point = (pointDiffuse + pointSpecular) * attenuation;"

//												// spot light
"	vec3 spotPosition = vec3(spotLight[0].x, spotLight[0].y, spotLight[0].z);"
"	vec3 spotColor = vec3(spotLight[1].x, spotLight[1].y, spotLight[1].z);"
"	vec3 spotOrientation = vec3(spotLight[2].x, spotLight[2].y, spotLight[2].z);"
"	float spotConstant = spotLight[3].x;"
"	float spotLinear = spotLight[3].y;"
"	float spotQuadratic = spotLight[3].z;"

// Diffuse 
"	vec3 spotNorm = normalize(normal);"
"	vec3 spotLightDir = normalize(spotPosition - fs_in.FragPos);"
"	float spotDiff = max(dot(spotNorm, spotLightDir), 0.0);"
"	vec3 spotDiffuse = spotColor * spotDiff;"

// Specular
"	vec3 spotViewDir = normalize(cameraPos - fs_in.FragPos);"
"	vec3 spotReflectDir = reflect(-spotLightDir, spotNorm);"
"	float spotSpec = pow(max(dot(spotViewDir, spotReflectDir), 0.0), materialShininess);"
"	vec3 spotSpecular = spotColor * spotSpec;"

// Spotlight (soft edges)
"	float spotTheta = dot(spotLightDir, normalize(-spotOrientation));"
"	float spotEpsilon = (spotCutOffs.x - spotCutOffs.y);"
"	float spotIntensity = clamp((spotTheta - spotCutOffs.y) / spotEpsilon, 0.0, 1.0);"
"	spotDiffuse *= spotIntensity;"
"	spotSpecular *= spotIntensity;"

// Attenuation
"	float spotDistance = length(spotPosition - fs_in.FragPos);"
"	float spotAttenuation = 1.0f / (spotConstant + spotLinear * spotDistance + spotQuadratic * (spotDistance * spotDistance));"
"	spotDiffuse *= spotAttenuation;"
"	spotSpecular *= spotAttenuation;"

"	spot = spotDiffuse + spotSpecular;"

"	color = texture(diffuseMap, fs_in.TexCoord) * vec4( ambient + directional + point + spot, 1.0);"
//"	color = vec4(1.0) * vec4( ambient + directional + point + spot, 1.0);"
"}" };

//*/

// shader 2
const GLchar* vertexShaderSource = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 position;"
	"layout(location = 2) in vec2 texCoords;"

	"out VS_OUT{"
	"	vec2 texCoords;"
	"} vs_out;"

	//"uniform mat4 projection;"
	//"uniform mat4 view;"
	//"uniform mat4 model;"

	"uniform mat4 viewMatrix;"
	"uniform mat4 modelMatrix;"

	"void main()\n"
	"{"
	"	gl_Position = viewMatrix * modelMatrix * vec4(position, 1.0f);"
	"	vs_out.texCoords = texCoords;"
	"}"
};

const GLchar* geometryShaderSource = {
"#version 330 core\n"
"layout(triangles) in;"
"layout(triangle_strip, max_vertices = 3) out;"

"in VS_OUT{"
"	vec2 texCoords;"
"} gs_in[];"

"out vec2 TexCoords;"

"uniform float explosionMagnitude;"

"vec4 explode(vec4 position, vec3 normal)"
"{"
"	float magnitude = 2.0f;"
"	vec3 direction = normal * explosionMagnitude;"
"	return position + vec4(direction, 0.0f);"
"}"

"vec3 GetNormal()"
"{"
"	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);"
"	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);"
"	return normalize(cross(a, b));"
"}"

"void main() {"
"	vec3 normal = GetNormal();"

"	gl_Position = explode(gl_in[0].gl_Position, normal);"
"	TexCoords = gs_in[0].texCoords;"
"	EmitVertex();"
"	gl_Position = explode(gl_in[1].gl_Position, normal);"
"	TexCoords = gs_in[1].texCoords;"
"	EmitVertex();"
"	gl_Position = explode(gl_in[2].gl_Position, normal);"
"	TexCoords = gs_in[2].texCoords;"
"	EmitVertex();"
"	EndPrimitive();"
"}"
};

const GLchar* fragmentShaderSource = {
	"#version 330 core\n"
	"in vec2 TexCoords;"
	"out vec4 color;"

	"uniform sampler2D texture_diffuse1;"

	"void main()"
	"{"
	"	color = texture(texture_diffuse1, TexCoords);"
	"}"
};

Shader::Shader()
{
	// Build and compile shader program

	// Vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Geometry shader
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
	glCompileShader(geometryShader);

	// Check for compile time errors
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
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

Shader::~Shader()
{
	glDeleteShader(vertexShader);
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