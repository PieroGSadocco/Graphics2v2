#version 330 core


layout (std140) uniform ambientLights
{
	vec4 numAmbientLightsPadPadPad;
    vec4 amb[3];
};

layout (std140) uniform directionalLights
{
	vec4 numDirectionalLightsPadPadPad;
    mat4x2 dir[3];
};


in VS_OUT{
	vec2 texCoords;
	vec3 normals;
	vec3 tangents;
	vec3 biTangents;
} vs_out;


out vec4 color;


uniform sampler2D texture_diffuse1;


void main()
{
	vec4 ambientLight = 	vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 directionalLight = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	for(int i = 0; i < numAmbientLightsPadPadPad.x; ++i)
	{
		ambientLight = ambientLight + amb[i];
	}
	
	for(int i = 0; i < numDirectionalLightsPadPadPad.x; ++i)
	{
		// organize data	
		vec3 directionalOrientation = vec3(1.0f,0.0f,0.0f);//vec3(dir[i][0].y, dir[i][1].y, dir[i][2].y);
		vec3 directionalColor = vec3(1.0f,1.0f,1.0f);
		
		// diffuse
		vec3 directionalNorm = normalize(vs_out.normals);
		vec3 directionalLightDir = normalize(-directionalOrientation);
		float directionalDiff = max(dot(directionalNorm, directionalLightDir), 0.0);
		vec3 directionalDiffuse = directionalDiff * directionalColor;
		
		
		
		
		
		
		
		
		directionalLight = vec4(directionalDiffuse, 1.0f);// + (directionalSpecular);
	}

	color = texture(texture_diffuse1, vs_out.texCoords) * (ambientLight + directionalLight) ;
}