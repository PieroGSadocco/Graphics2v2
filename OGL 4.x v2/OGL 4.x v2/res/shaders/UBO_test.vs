#version 330 core
layout(location = 0) in vec3 positions;
layout(location = 1) in vec4 colors;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 normals;
layout(location = 4) in vec3 tangents;
layout(location = 5) in vec3 biTangents;

out VS_OUT{
	vec2 texCoords;
	vec3 normals;
	vec3 tangents;
	vec3 biTangents;
} vs_out;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;



void main()
{
	gl_Position = viewMatrix * modelMatrix * vec4(positions, 1.0f);
	vs_out.texCoords = texCoords;
	vs_out.normals = normals;
	vs_out.tangents = tangents;
	vs_out.biTangents = biTangents;
}