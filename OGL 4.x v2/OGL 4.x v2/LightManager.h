#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "GL\glew.h"
#include "GL\wglew.h"

#include <vector>

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "Shader.h"

const unsigned int ambientLightBindingIndex = 0;
const unsigned int directionalLightBindingIndex = 1;
const unsigned int pointLightBindingIndex = 2;
const unsigned int spotLightBindingIndex = 3;

struct Light
{
	Light(float _colR, float _colG, float _colB)
	{
		colR = _colR;
		colG = _colG;
		colB = _colB;
	}

	float colR;
	float colG;
	float colB;
	float padding;
};

class LightManager
{
public:
	LightManager(unsigned int _maxAmbLights);
	~LightManager();

	void AddLight(Light _light);
	void AddLight(DirectionalLight _light);
	void AddLight(PointLight _light);
	void AddLight(SpotLight _light);

	void Update();
	void Bind(GLuint _shaderProgram, GLuint _shaderAmbientLightUniform, GLuint _shaderDirectionalLightUniform, GLuint _shaderPointLightUniform, GLuint _shaderSpotLightUniform);

private:
	std::vector<Light> ambientLights;

	//std::vector<AmbientLight> ambientLights;
	//std::vector<DirectionalLight> directionalLights;
	//std::vector<PointLight> pointLights;
	//std::vector<SpotLight> spotLights;

	bool ambientLightUpdate;
	//bool directionalLightUpdate;
	//bool pointLightUpdate;
	//bool spotLightUpdate;

	unsigned int maxAmbientLights;
	unsigned int maxDirectionalLights;
	unsigned int maxPointLights;
	unsigned int maxSpotLights;

	GLuint ambientLightUBO;
	//GLuint directionalLightUBO;
	//GLuint pointLightUBO;
	//GLuint spotLightUBO;
};

#endif