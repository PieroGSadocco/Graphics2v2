#include "Mesh.h"

//*
#include "Loader.h"

GLfloat vertices[] = 
{
	// Position						// Colors					// UVs				// Normals
	//front
	+1.0f, +1.0f, +1.0f, 1.0f,		0.5f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, +1.0f,
	+1.0f, -1.0f, +1.0f, 1.0f,		0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f,		0.0f, 0.0f, +1.0f,
	-1.0f, -1.0f, +1.0f, 1.0f,		0.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, +1.0f,
	-1.0f, +1.0f, +1.0f, 1.0f,		0.5f, 0.5f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, 0.0f, +1.0f,
	//back
	+1.0f, +1.0f, -1.0f, 1.0f,		0.5f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
	+1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	-1.0f, +1.0f, -1.0f, 1.0f,		0.5f, 0.5f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
	//top
	+1.0f, +1.0f, +1.0f, 1.0f,		0.5f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, +1.0f, 0.0f,
	+1.0f, +1.0f, -1.0f, 1.0f,		0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f,		0.0f, +1.0f, 0.0f,
	-1.0f, +1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f,		0.0f, +1.0f, 0.0f,
	-1.0f, +1.0f, +1.0f, 1.0f,		0.5f, 0.5f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, +1.0f, 0.0f,
	//bottom
	+1.0f, -1.0f, +1.0f, 1.0f,		0.5f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	+1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, +1.0f, 1.0f,		0.5f, 0.5f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	//right
	+1.0f, +1.0f, +1.0f, 1.0f,		0.5f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		+1.0f, 0.0f, 0.0f,
	+1.0f, +1.0f, -1.0f, 1.0f,		0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f,		+1.0f, 0.0f, 0.0f,
	+1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f,		+1.0f, 0.0f, 0.0f,
	+1.0f, -1.0f, +1.0f, 1.0f,		0.5f, 0.5f, 0.0f, 1.0f,		0.0f, 1.0f,		+1.0f, 0.0f, 0.0f,
	//left
	-1.0f, +1.0f, +1.0f, 1.0f,		0.5f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-1.0f, +1.0f, -1.0f, 1.0f,		0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-1.0f, -1.0f, +1.0f, 1.0f,		0.5f, 0.5f, 0.0f, 1.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
};

GLuint indices[] = 
{  
	0, 1, 3,
	1, 2, 3,

	4, 5, 7,
	5, 6, 7,

	8, 9, 11,
	9, 10, 11,

	12, 13, 15,
	13, 14, 15,

	16, 17, 19,
	17, 18, 19,

	20, 21, 23,
	21, 22, 23,
};

Mesh::Mesh()
{
	numIndices = sizeof(indices) / sizeof(GLuint);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// UV attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(GLfloat), (GLvoid*)(10 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

Mesh::Mesh(std::string _path)
{
	Loader loader;
	//loader.LoadWithAssimp(_path,*(Mesh*)this);
	loader.LoadOBJ(_path, *(Mesh*)this);
}

void Mesh::SetUpData(std::vector<float>& _vertexData, std::vector<unsigned int>& _indexData)
{
	numIndices = _indexData.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertexData.size() * sizeof(float), (void*)&_vertexData.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexData.size() * sizeof(float), (void*)&_indexData[0], GL_STATIC_DRAW);

	// Position attribute 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute 1
	// UV attribute 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute 3
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	// tangent attribute
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(4);
	// bitangent attribute
	//glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Bind()
{
	glBindVertexArray(VAO);
}

void Mesh::UnBind()
{
	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}
//*/
/*
Mesh::Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices, std::vector<TextureStruct> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexStruct), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStruct),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (GLvoid*)offsetof(VertexStruct, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (GLvoid*)offsetof(VertexStruct, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	//// Bind appropriate textures
	//GLuint diffuseNr = 1;
	//GLuint specularNr = 1;
	//for (GLuint i = 0; i < this->textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
	//									  // Retrieve texture number (the N in diffuse_textureN)
	//	stringstream ss;
	//	string number;
	//	string name = this->textures[i].type;
	//	if (name == "texture_diffuse")
	//		ss << diffuseNr++; // Transfer GLuint to stream
	//	else if (name == "texture_specular")
	//		ss << specularNr++; // Transfer GLuint to stream
	//	number = ss.str();
	//	// Now set the sampler to the correct texture unit
	//	glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);
	//	// And finally bind the texture
	//	glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	//}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	//glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//// Always good practice to set everything back to defaults once configured.
	//for (GLuint i = 0; i < this->textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}
}
*/












