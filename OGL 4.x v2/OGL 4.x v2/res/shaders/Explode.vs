#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoords;

out VS_OUT{
	vec2 texCoords;
} vs_out;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = viewMatrix * modelMatrix * vec4(position, 1.0f);
	vs_out.texCoords = texCoords;
}