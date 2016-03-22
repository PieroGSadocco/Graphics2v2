#version 330 core

in VS_OUT{
	vec2 texCoords;
} fs_in;

out vec4 color;

uniform sampler2D renderedMap;

void main()
{
//color = vec4(1.0f,1.0f,1.0f,1.0f);
	color = texture(renderedMap, fs_in.texCoords);
}