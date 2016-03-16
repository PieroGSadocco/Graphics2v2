#version 330 core

in VS_OUT
{
	vec3 color;
	vec4 vertexColor;
	
	vec3 FragPos;
	vec2 TexCoord;
	
	vec3 Normal;
	vec3 Tangent;
	vec3 BiTangent;
} fs_in;

in vec4 vertexColor;

out vec4 color;

uniform sampler2D normalMap;
uniform sampler2D diffuseMap;

uniform vec3 cameraPos;

uniform vec3 ambientLight;
uniform mat4x2 directionalLight;
uniform mat3 pointLight;
uniform mat4x3 spotLight;
uniform vec2 spotCutOffs;

void main()
{
	vec3 ambient = vec3(0.0, 0.0, 0.0);
	vec3 directional = vec3(0.0, 0.0, 0.0);
	vec3 point = vec3(0.0, 0.0, 0.0);
	vec3 spot = vec3(0.0, 0.0, 0.0);

	float materialShininess = 256;
//												// normal map
	bool normalMapping = true;
	vec3 normal = normalize(fs_in.Normal);

	if(normalMapping == true)
	{
		normal = texture(normalMap, fs_in.TexCoord).rgb;
		normal = normalize(normal * 2.0 - 1.0);

		// Skyrim Snow?
		//normal = normalize(normal * normalize(fs_in.Normal));
	}



//												// ambient light
	ambient = ambientLight;

//												// directional light
// organize data	
	vec3 directionalOrientation = vec3(directionalLight[0].x, directionalLight[1].x, directionalLight[2].x);
	vec3 directionalColor = vec3(directionalLight[0].y, directionalLight[1].y, directionalLight[2].y);
	float directionalIntensity = directionalLight[3].x;

// diffuse
	vec3 directionalNorm = normalize(normal);
	vec3 directionalLightDir = normalize(-directionalOrientation);
	float directionalDiff = max(dot(directionalNorm, directionalLightDir), 0.0);
	vec3 directionalDiffuse = directionalDiff * directionalColor;

// specular
	vec3 directionalViewDir = normalize(cameraPos - fs_in.FragPos);
	vec3 directionalReflectDir = reflect(-directionalLightDir, directionalNorm);
	float directionalSpec = pow(max(dot(directionalViewDir, directionalReflectDir), 0.0), materialShininess);
	vec3 directionalSpecular = directionalSpec * directionalColor;

	directional = (directionalDiffuse) + (directionalSpecular);

//												// point light
// organize data	
	vec3 pointPosition = vec3(pointLight[0].x, pointLight[0].y, pointLight[0].z);
	vec3 pointColor = vec3(pointLight[1].x, pointLight[1].y, pointLight[1].z);
	float pointConstant = pointLight[2].x;
	float pointLinear = pointLight[2].y;
	float pointQuadratic = pointLight[2].z;

// diffuse
	vec3 pointNorm = normalize(normal);
	vec3 pointLightDir = normalize(pointPosition - fs_in.FragPos);
	float pointDiff = max(dot(pointNorm, pointLightDir), 0.0);
	vec3 pointDiffuse = pointColor * pointDiff;

// specular
	vec3 pointViewDir = normalize(cameraPos - fs_in.FragPos);
	vec3 pointReflectDir = reflect(-pointLightDir, pointNorm);
	float pointSpec = pow(max(dot(pointViewDir, pointReflectDir), 0.0), materialShininess);
	vec3 pointSpecular = pointColor * pointSpec;

// attenuation
	float distance = length(pointPosition - fs_in.FragPos)*2;
	float attenuation = 1.0f / (pointConstant + pointLinear * distance + pointQuadratic * (distance * distance));

	point = (pointDiffuse + pointSpecular) * attenuation;

//												// spot light
// organize data	
	vec3 spotPosition = vec3(spotLight[0].x, spotLight[0].y, spotLight[0].z);
	vec3 spotColor = vec3(spotLight[1].x, spotLight[1].y, spotLight[1].z);
	vec3 spotOrientation = vec3(spotLight[2].x, spotLight[2].y, spotLight[2].z);
	float spotConstant = spotLight[3].x;
	float spotLinear = spotLight[3].y;
	float spotQuadratic = spotLight[3].z;

// Diffuse 
	vec3 spotNorm = normalize(normal);
	vec3 spotLightDir = normalize(spotPosition - fs_in.FragPos);
	float spotDiff = max(dot(spotNorm, spotLightDir), 0.0);
	vec3 spotDiffuse = spotColor * spotDiff;

// Specular
	vec3 spotViewDir = normalize(cameraPos - fs_in.FragPos);
	vec3 spotReflectDir = reflect(-spotLightDir, spotNorm);
	float spotSpec = pow(max(dot(spotViewDir, spotReflectDir), 0.0), materialShininess);
	vec3 spotSpecular = spotColor * spotSpec;

// Spotlight (soft edges)
	float spotTheta = dot(spotLightDir, normalize(-spotOrientation));
	float spotEpsilon = (spotCutOffs.x - spotCutOffs.y);
	float spotIntensity = clamp((spotTheta - spotCutOffs.y) / spotEpsilon, 0.0, 1.0);
	spotDiffuse *= spotIntensity;
	spotSpecular *= spotIntensity;

// Attenuation
	float spotDistance = length(spotPosition - fs_in.FragPos);
	float spotAttenuation = 1.0f / (spotConstant + spotLinear * spotDistance + spotQuadratic * (spotDistance * spotDistance));
	spotDiffuse *= spotAttenuation;
	spotSpecular *= spotAttenuation;

	spot = spotDiffuse + spotSpecular;

	color = texture(diffuseMap, fs_in.TexCoord) * vec4( ambient + directional + point + spot, 1.0);
//	color = vec4(1.0) * vec4( ambient + directional + point + spot, 1.0);
}