#include "LightManager.h"

#include "Logger.h"

LightManager::LightManager(unsigned int _maxAmbLights)
{
	std::string str = "";

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &nrAttributes);
	maxAmbientLights = nrAttributes/16; // cuz padding

	str = std::string(""); str += "Maximum number of ambient lights supported: "; str += std::to_string(maxAmbientLights); str += " (Bacause it's super necessary to have more than one!)";
	Logger::Log(str);

	ambientLightUpdate = false;
	//directionalLightUpdate = false;
	//pointLightUpdate = false;
	//spotLightUpdate = false;
	
	//AddLight(AmbientLight(0.1f, 0.1f, 0.5f));
	//AddLight(DirectionalLight(0.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.5f));
	//AddLight(PointLight(2.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.09f, 0.032f));
	//AddLight(SpotLight(-1.5f, 5.0f, -4.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.09f, 0.032f, 5.5f, 10.0f));
	
	
	//glGenBuffers(1, &ambientLightUBO);
	//glBindBuffer(GL_UNIFORM_BUFFER, ambientLightUBO);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(AmbientLight) * ambientLights.size(), ambientLights.data(), GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//
	//glGenBuffers(1, &directionalLightUBO);
	//glBindBuffer(GL_UNIFORM_BUFFER, directionalLightUBO);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(DirectionalLight) * directionalLights.size(), directionalLights.data(), GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//
	//glGenBuffers(1, &pointLightUBO);
	//glBindBuffer(GL_UNIFORM_BUFFER, pointLightUBO);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLight) * pointLights.size(), pointLights.data(), GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//
	//glGenBuffers(1, &spotLightUBO);
	//glBindBuffer(GL_UNIFORM_BUFFER, spotLightUBO);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(SpotLight) * spotLights.size(), spotLights.data(), GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

LightManager::~LightManager()
{
	//glDeleteBuffers(1, &ambientLightUBO);
	//glDeleteBuffers(1, &directionalLightUBO);
	//glDeleteBuffers(1, &pointLightUBO);
	//glDeleteBuffers(1, &spotLightUBO);
}

void LightManager::AddLight(Light _light)
{
}

void LightManager::AddLight(DirectionalLight _light)
{
	//directionalLightUpdate = true;
	//directionalLights.push_back(_light);
}

void LightManager::AddLight(PointLight _light)
{
	//pointLightUpdate = true;
	//pointLights.push_back(_light);
}

void LightManager::AddLight(SpotLight _light)
{
	//spotLightUpdate = true;
	//spotLights.push_back(_light);
}

void LightManager::Update()
{
	
	
	//if (directionalLightUpdate)
	//{
	//	glBindBuffer(GL_UNIFORM_BUFFER, directionalLightUBO);
	//	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	//	memcpy(p, &directionalLights, sizeof(AmbientLight) * directionalLights.size());
	//	glUnmapBuffer(GL_UNIFORM_BUFFER);
	//}
	//
	//if (pointLightUpdate)
	//{
	//	glBindBuffer(GL_UNIFORM_BUFFER, pointLightUBO);
	//	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	//	memcpy(p, &pointLights, sizeof(AmbientLight) * pointLights.size());
	//	glUnmapBuffer(GL_UNIFORM_BUFFER);
	//}
	//
	//if (spotLightUpdate)
	//{
	//	glBindBuffer(GL_UNIFORM_BUFFER, spotLightUBO);
	//	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	//	memcpy(p, &spotLights, sizeof(AmbientLight) * spotLights.size());
	//	glUnmapBuffer(GL_UNIFORM_BUFFER);
	//}	
}

void LightManager::Bind(GLuint _shaderProgram, GLuint _shaderAmbientLightUniform, GLuint _shaderDirectionalLightUniform, GLuint _shaderPointLightUniform, GLuint _shaderSpotLightUniform)
{
	
	//
	////bind to a specific location
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, ambientLightUBO);
	////bind to the shader
	//glUniformBlockBinding(_shaderProgram, _shaderAmbientLightUniform, 0);
	//
	//
	////bind to a specific location
	//glBindBufferBase(GL_UNIFORM_BUFFER, 1, directionalLightUBO);
	////bind to the shader
	//glUniformBlockBinding(_shaderProgram, _shaderAmbientLightUniform, 1);
	//
	//
	////bind to a specific location
	//glBindBufferBase(GL_UNIFORM_BUFFER, 2, pointLightUBO);
	////bind to the shader
	//glUniformBlockBinding(_shaderProgram, _shaderAmbientLightUniform, 2);
	//
	//
	////bind to a specific location
	//glBindBufferBase(GL_UNIFORM_BUFFER, 3, spotLightUBO);
	////bind to the shader
	//glUniformBlockBinding(_shaderProgram, _shaderAmbientLightUniform, 3);
}

//reference
//http://www.geeks3d.com/20140704/gpu-buffers-introduction-to-opengl-3-1-uniform-buffers-objects/