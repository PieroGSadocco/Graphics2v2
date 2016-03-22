#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

struct AmbientLight {
	vec3 color;
} ambientLight_data;

//directionalLight_data
//pointLight_data
//spotLight_data

layout (location = 0) uniform amb_data_layout
{
	vec3 color2;
};

uniform AmbientLight ambientLights;

uniform sampler2D normalMap;
uniform sampler2D diffuseMap;

vec3 CalcAmbientLight();



void main()
{
	vec3 result;
	
	vec3 norm = normalize(Normal);
	//vec3 viewDir = normalize(viewPos - FragPos);
	
	result += CalcAmbientLight();
	
	color = texture(diffuseMap, TexCoords) * vec4(result, 1.0f);
}



vec3 CalcAmbientLight()
{
	return vec3(ambientLight_data.color[0]);
	return vec3(1.0f,1.0f,1.0f);
}