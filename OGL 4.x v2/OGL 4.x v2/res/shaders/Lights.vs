#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 biTangent;

out VS_OUT
{
	vec3 color;
	vec4 vertexColor;
	
	vec3 FragPos;
	vec2 TexCoord;
	
	vec3 Normal;
	vec3 Tangent;
	vec3 BiTangent;
	
	vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = viewMatrix * modelMatrix * position;

	vs_out.FragPos = vec3(modelMatrix * vec4(position.xyz, 1.0));
	vs_out.TexCoord = texCoord;

	vs_out.vertexColor = color;
	vs_out.color = color.rgb;
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
	vs_out.Normal = normalize(normalMatrix * normal);
	vs_out.Tangent = normalize(normalMatrix * tangent);
	vs_out.BiTangent = normalize(normalMatrix * biTangent);
	
	
	
	
	//mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * biTangent);
    vec3 N = normalize(normalMatrix * normal);    
    
    mat3 TBN = transpose(mat3(T, B, N));  
    //vs_out.TangentLightPos = TBN * lightPos;
    //vs_out.TangentViewPos  = TBN * viewPos;
    //vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}