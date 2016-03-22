#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 biTangent;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = viewMatrix *  modelMatrix * position;
    FragPos = vec3(modelMatrix * position);
	Normal = normal;
    //Normal = mat3(transpose(inverse(modelMatrix))) * normal;  
    TexCoords = texCoord;
} 