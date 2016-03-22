#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

struct AmbientLight
{
	vec3 color;
}

//struct DirectionalLight
//{
//	vec3 direction;
//	vec3 color;
//}
//
//struct PointLight
//{
//	vec3 position;
//	
//	vec3 color;
//	
//	float constant;
//	float linear;
//	float quadratic;
//}
//
//struct SpotLight
//{
//	vec3 position;
//	vec3 direction;
//	vec3 color;
//	
//	float cutOff;
//	float outerCutOff;
//	
//	float constant;
//	float linear;
//	float quadratic;
//}

uniform AmbientLight ambientLights;
//uniform DirectionalLight directionalLights;
//uniform PointLight pointLights;
//uniform SpotLight spotLights;

vec3 CalcAmbientLight(AmbientLight light);
//vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 output;
	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	output += CalcAmbientLight();
	
	//for(int i = 0; i != numDirectionalLights; ++i)
	//{
	//	output += CalcDirectionalLight(directionalLights[i], norm, FragPos, viewDir);
	//}
	//
	//for(int i = 0; i != numPointLights; ++i)
	//{
	//	output += CalcPointLight();
	//}
	//
	//for(int i = 0; i != numSpotLights; ++i)
	//{
	//	output += CalcSpotLight();
	//}
	
	color = vec4(output, 1.0f);
}



vec3 CalcAmbientLight(DirectionalLight light)
{
	return vec3(light.color);
}

//vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
//{
//	vec3 lightDir = normalize(-light.direction);
//	// Diffuse
//	float diff = max(dot(normal, lightDir), 0.0);
//	
//	// Specular
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	
//	// Combine results
//	//vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//	vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//	return (diffuse + specular);
//}
//
//vec3 CalcPointLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//	vec3 lightDir = normalize(light.position - fragPos);
//	
//	// Diffuse
//	float diff = max(dot(normal, lightDir), 0.0);
//	
//	// Specular
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	
//	// Attenuation
//	float distance    = length(light.position - fragPos);
//	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//	
//	// Combine results
//	//vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//	vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//	//ambient  *= attenuation;
//	diffuse  *= attenuation;
//	specular *= attenuation;
//	return (diffuse + specular);
//}
//
//vec3 CalcSpotLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//	vec3 lightDir = normalize(light.position - fragPos);
//    // Diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // Specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // Attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//    // Spotlight intensity
//    float theta = dot(lightDir, normalize(-light.direction)); 
//    float epsilon = light.cutOff - light.outerCutOff;
//    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//    // Combine results
//    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    ambient *= attenuation * intensity;
//    diffuse *= attenuation * intensity;
//    specular *= attenuation * intensity;
//    return (ambient + diffuse + specular);
//}