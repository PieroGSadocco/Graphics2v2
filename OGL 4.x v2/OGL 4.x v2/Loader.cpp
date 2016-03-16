#include "Loader.h"

#include "Logger.h"
#include <string>

void Loader::LoadOBJ(std::string _path, Mesh& _mesh)
{
	std::vector<float> positions;
	std::vector<float> uvs;
	std::vector<float> normals;
	std::vector<float> tangent;
	std::vector<float> bitangent;

	struct VertexIndices
	{
		unsigned int positionIndex;
		unsigned int uvIndex;
		unsigned int normalIndex;

		bool operator==(const VertexIndices& _other)
		{
			return (positionIndex == _other.positionIndex && uvIndex == _other.uvIndex && normalIndex == _other.normalIndex);
		}
	};

	std::vector<VertexIndices> verticesIndices;

	std::vector<float> data;
	std::vector<unsigned int> indices;

	std::ifstream file(_path);

	if (!file.is_open())
	{
		std::string str = "ERROR: Failed to open: \""; str += _path; str += "\";";
		Logger::Log(str);
		return;
	}

	char charBuffer[256];

	while (!file.eof())
	{
		file.getline(charBuffer, 256);

		char floatBuffer[10];
		short floatBufferIndex = 0;

		if (charBuffer[0] == 'v' && charBuffer[1] == ' ')
		{// store xyz
			for (unsigned int i = 2; ; ++i)
			{
				if (charBuffer[i] == ' ')
				{
					floatBuffer[floatBufferIndex] = '\0';
					floatBufferIndex = 0;
					positions.push_back((float)std::atof(floatBuffer));
					for (unsigned short j = 0; floatBuffer[j] != '\0'; ++j)
						floatBuffer[j] = '\0';
				}
				else if (charBuffer[i] == '\0')
				{
					floatBuffer[floatBufferIndex] = '\0';
					floatBufferIndex = 0;
					positions.push_back((float)std::atof(floatBuffer));
					for (unsigned short j = 0; floatBuffer[j] != '\0'; ++j)
						floatBuffer[j] = '\0';
					break;
				}
				else
				{
					floatBuffer[floatBufferIndex] = charBuffer[i];
					floatBufferIndex++;
				}
			}
		}
		else if (charBuffer[0] == 'v' && charBuffer[1] == 't' && charBuffer[2] == ' ')
		{// store xyz
			for (unsigned int i = 3; ; ++i)
			{
				if (charBuffer[i] == ' ')
				{
					floatBuffer[floatBufferIndex] = '\0';
					floatBufferIndex = 0;
					uvs.push_back((float)std::atof(floatBuffer));
					for (unsigned short j = 0; floatBuffer[j] != '\0'; ++j)
						floatBuffer[j] = '\0';
				}
				else if (charBuffer[i] == '\0')
				{
					floatBuffer[floatBufferIndex] = '\0';
					floatBufferIndex = 0;
					uvs.push_back((float)std::atof(floatBuffer));
					for (unsigned short j = 0; floatBuffer[j] != '\0'; ++j)
						floatBuffer[j] = '\0';
					break;
				}
				else
				{
					floatBuffer[floatBufferIndex] = charBuffer[i];
					floatBufferIndex++;
				}
			}
		}
		else if (charBuffer[0] == 'v' && charBuffer[1] == 'n' && charBuffer[2] == ' ')
		{// store xyz
			for (unsigned int i = 3; ; ++i)
			{
				if (charBuffer[i] == ' ')
				{
					floatBuffer[floatBufferIndex] = '\0';
					floatBufferIndex = 0;
					normals.push_back((float)std::atof(floatBuffer));
					for (unsigned short j = 0; floatBuffer[j] != '\0'; ++j)
						floatBuffer[j] = '\0';
				}
				else if (charBuffer[i] == '\0')
				{
					floatBuffer[floatBufferIndex] = '\0';
					floatBufferIndex = 0;
					normals.push_back((float)std::atof(floatBuffer));
					for (unsigned short j = 0; floatBuffer[j] != '\0'; ++j)
						floatBuffer[j] = '\0';
					break;
				}
				else
				{
					floatBuffer[floatBufferIndex] = charBuffer[i];
					floatBufferIndex++;
				}
			}
		}
		else if (charBuffer[0] == 's')
		{// go to next step
			break;
		}
	}

	// find face type
	short type = 0;

	if (positions.size() > 0)
		type++;
	if (uvs.size() > 0)
		type++;
	if (normals.size() > 0)
		type++;

	//char intBuffer[10];
	short floatIndex = 0;

	if (type == 3)
	{// 3 data per face // store face data
		while (!file.eof())
		{
			file.getline(charBuffer, 256);

			char integer3Buffer[32];
			short integerBufferIndex = 0;

			if (charBuffer[0] == 'f' && charBuffer[1] == ' ')
			{// store vertices indices
				for (unsigned int i = 2; ; ++i)
				{
					if (charBuffer[i] == '\0' || charBuffer[i] == ' ')
					{
						integer3Buffer[integerBufferIndex] = '\0';
						integerBufferIndex = 0;
						VertexIndices newVertexIndices;
						//parse
						char integerBuffer[32];
						unsigned int integerBufferIndex = 0;
						unsigned int j = 0;
						for (; ; ++j)
						{//populate buffer
							if (integer3Buffer[j] == '/')
							{
								integerBuffer[j] = '\0';
								newVertexIndices.positionIndex = std::stoi(integerBuffer);
								for (unsigned short k = 0; integerBuffer[k] != '\0'; ++k)
									integerBuffer[k] = '\0';
								integerBufferIndex = 0;
								break;
							}
							else
							{
								integerBuffer[integerBufferIndex] = integer3Buffer[j];
								++integerBufferIndex;
							}
						}
						
						++j;
						for ( ; ;++j)
						{//populate buffer
							if (integer3Buffer[j] == '/')
							{
								integerBuffer[j] = '\0';
								newVertexIndices.uvIndex = std::stoi(integerBuffer);
								for (unsigned short k = 0; integerBuffer[k] != '\0'; ++k)
									integerBuffer[k] = '\0';
								integerBufferIndex = 0;
								break;
							}
							else
							{
								integerBuffer[integerBufferIndex] = integer3Buffer[j];
								++integerBufferIndex;
							}
						}

						++j;
						for ( ; ;++j)
						{//populate buffer
							if (integer3Buffer[j] == '\0' || integer3Buffer[j] == ' ')
							{
								integerBuffer[j] = '\0';
								newVertexIndices.normalIndex = std::stoi(integerBuffer);
								for (unsigned short k = 0; integerBuffer[k] != '\0'; ++k)
									integerBuffer[k] = '\0';
								break;
							}
							else
							{
								integerBuffer[integerBufferIndex] = integer3Buffer[j];
								++integerBufferIndex;
							}
						}
						verticesIndices.push_back(newVertexIndices);

						for (unsigned short k = 0; integer3Buffer[k] != '\0'; ++k)
							integer3Buffer[k] = '\0';

						if (charBuffer[i] == '\0')
							break;
					}
					else
					{
						integer3Buffer[integerBufferIndex] = charBuffer[i];
						integerBufferIndex++;
					}
				}
			}
		}
	}

	// OBJ fully loaded

	// Create tangents and bitangents
	//for (unsigned int i = 0; i != verticesIndices.size(); i += 3)
	//{
	//	int pI = verticesIndices[i].positionIndex - 1;
	//	int uvI = verticesIndices[i].uvIndex - 1;
	//	int nI = verticesIndices[i].normalIndex - 1;
	//
	//	float px = positions[pI * 3];
	//
	//	glm::vec3 pos1(positions[verticesIndices[i + 0].positionIndex], positions[verticesIndices[i + 0].positionIndex + 1], positions[verticesIndices[i + 0].positionIndex + 2]);
	//	glm::vec3 pos2(positions[verticesIndices[i + 1].positionIndex], positions[verticesIndices[i + 1].positionIndex + 1], positions[verticesIndices[i + 1].positionIndex + 2]);
	//	glm::vec3 pos3(positions[verticesIndices[i + 2].positionIndex], positions[verticesIndices[i + 2].positionIndex + 1], positions[verticesIndices[i + 2].positionIndex + 2]);
	//
	//	glm::vec2 uv1(uvs[verticesIndices[i + 0].positionIndex], uvs[verticesIndices[i + 0].positionIndex + 1]);
	//	glm::vec2 uv2(uvs[verticesIndices[i + 1].positionIndex], uvs[verticesIndices[i + 1].positionIndex + 1]);
	//	glm::vec2 uv3(uvs[verticesIndices[i + 2].positionIndex], uvs[verticesIndices[i + 2].positionIndex + 1]);
	//
	//	glm::vec3 nm(normals[i], normals[i + 1], normals[i + 2]);
	//
	//	glm::vec3 edge1 = pos2 - pos1;
	//	glm::vec3 edge2 = pos3 - pos1;
	//	glm::vec2 deltaUV1 = uv2 - uv1;
	//	glm::vec2 deltaUV2 = uv3 - uv1;
	//
	//	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	//
	//	glm::vec3 tangent1;
	//	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	//	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	//	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	//	tangent1 = glm::normalize(tangent1);
	//
	//	glm::vec3 bitangent1;
	//	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	//	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	//	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	//	bitangent1 = glm::normalize(bitangent1);
	//
	//	tangent.push_back(tangent1.x);
	//	tangent.push_back(tangent1.y);
	//	tangent.push_back(tangent1.z);
	//	tangent.push_back(tangent1.x);
	//	tangent.push_back(tangent1.y);
	//	tangent.push_back(tangent1.z);
	//	tangent.push_back(tangent1.x);
	//	tangent.push_back(tangent1.y);
	//	tangent.push_back(tangent1.z);
	//
	//	bitangent.push_back(bitangent1.x);
	//	bitangent.push_back(bitangent1.y);
	//	bitangent.push_back(bitangent1.z);
	//	bitangent.push_back(bitangent1.x);
	//	bitangent.push_back(bitangent1.y);
	//	bitangent.push_back(bitangent1.z);
	//	bitangent.push_back(bitangent1.x);
	//	bitangent.push_back(bitangent1.y);
	//	bitangent.push_back(bitangent1.z);
	//}

	// Arrange data and indexes
	for (unsigned int i = 0; i != verticesIndices.size(); ++i)
	{
		// check for duplicate
		unsigned int found = UINT_MAX;
		for (unsigned int j = i; j > 0; --j)
		{
			if (verticesIndices[i] == verticesIndices[j-1])
			{
				found = j-1;
				break;
			}
		}

		if (found == UINT_MAX)
		{//false -> add new

			int pI = verticesIndices[i].positionIndex-1;
			int uvI = verticesIndices[i].uvIndex-1;
			int nI = verticesIndices[i].normalIndex - 1;
			int tI = i;
			int btI = i;

			float px = positions[pI*3];
			float py = positions[pI * 3 + 1];
			float pz = positions[pI * 3 + 2];

			float u = uvs[uvI * 2];
			float v = uvs[uvI * 2 + 1];

			float nx = normals[nI * 3];
			float ny = normals[nI * 3 + 1];
			float nz = normals[nI * 3 + 2];

			//float tx = tangent[tI * 3];
			//float ty = tangent[tI * 3 + 1];
			//float tz = tangent[tI * 3 + 2];

			//float btx = bitangent[btI * 3];
			//float bty = bitangent[btI * 3 + 1];
			//float btz = bitangent[btI * 3 + 2];

			data.push_back(px);
			data.push_back(py);
			data.push_back(pz);
			data.push_back(u);
			data.push_back(v);
			data.push_back(nx);
			data.push_back(ny);
			data.push_back(nz);

			indices.push_back(i);
		}
		else
		{//true -> use original
			indices.push_back(found-1);
		}
	}

	// data and indices organized



	// give data and indices to mesh
	_mesh.SetUpData(data, indices);
}

/*
void Loader::LoadBinaryMesh(std::string _path, MeshOGL*& _mesh, unsigned int& _numMeshes)
{
	struct MeshData
	{
		unsigned int dataType;

		unsigned int numData;
		float* data;

		unsigned int numIndices;
		unsigned int* indices;

		MeshData()
		{
			dataType = -1;
			numData = -1;
			numIndices = -1;
			data = nullptr;
			indices = nullptr;
		}

		~MeshData()
		{
			if (data != nullptr)
				delete[] data;
			if (indices != nullptr)
				delete[] indices;
		}
	};

	MeshData* meshes;

	//Load
	std::ifstream file(_path, std::ifstream::binary);

	file.read((char*)&_numMeshes, sizeof(unsigned int));

	meshes = new MeshData[_numMeshes];

	for (unsigned int i = 0; i != _numMeshes; ++i)
	{
		//type
		file.read((char*)&meshes[i].dataType, sizeof(unsigned int));
		//vert Size
		file.read((char*)&meshes[i].numData, sizeof(unsigned int));
		//vert Data
		meshes[i].data = new float[meshes[i].numData];
		file.read((char*)&(*meshes[i].data), meshes[i].numData * sizeof(float));
		//ind Size
		file.read((char*)&meshes[i].numIndices, sizeof(unsigned int));
		//ind Data
		meshes[i].indices = new unsigned int[meshes[i].numIndices];
		file.read((char*)&(*meshes[i].indices), meshes[i].numIndices * sizeof(unsigned int));
	}

	// OGL part
	_mesh = new MeshOGL[_numMeshes];

	for (unsigned int i = 0; i != _numMeshes; ++i)
	{
		_mesh->numIndices = meshes[i].numIndices;

		glGenVertexArrays(1, &_mesh->VAO);
		glGenBuffers(1, &_mesh->VBO);
		glGenBuffers(1, &_mesh->EBO);

		glBindVertexArray(_mesh->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, meshes[i].numData * sizeof(float), meshes[i].data, GL_STATIC_DRAW);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshes[i].numIndices * sizeof(unsigned int), meshes[i].indices, GL_STATIC_DRAW);
	
		// Position attribute //0, 1, 2
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// UV attribute // 3, 4
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		// Normal attribute // 5, 6, 7
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// release data
	delete[] meshes;
}
//*/

void Loader::LoadBinaryMesh2(std::string _path, MeshOGL*& _mesh, unsigned int& _numMeshes)
{
	struct MeshData
	{
		unsigned int positions;
		unsigned int uvs;
		unsigned int normals;
		unsigned int tangents;
		unsigned int biTangents;

		unsigned int numData;
		float* data;

		unsigned int numIndices;
		unsigned int* indices;

		MeshData()
		{
			positions = -1;
			uvs = -1;
			normals = -1;
			tangents = -1;
			biTangents = -1;

			numData = -1;
			numIndices = -1;

			data = nullptr;
			indices = nullptr;
		}

		~MeshData()
		{
			if (data != nullptr)
				delete[] data;
			if (indices != nullptr)
				delete[] indices;
		}
	};

	MeshData* meshes;

	//Load
	std::ifstream file(_path, std::ifstream::binary);

	if (!file.is_open())
	{
		std::string str = "ERROR: Failed to open: \""; str += _path; str += "\";";
		Logger::Log(str);
		return;
	}

	file.read((char*)&_numMeshes, sizeof(unsigned int));

	meshes = new MeshData[_numMeshes];

	for (unsigned int i = 0; i != _numMeshes; ++i)
	{
		//positions
		file.read((char*)&meshes[i].positions, sizeof(unsigned int));
		//uvs
		file.read((char*)&meshes[i].uvs, sizeof(unsigned int));
		//normals
		file.read((char*)&meshes[i].normals, sizeof(unsigned int));
		//tangents
		file.read((char*)&meshes[i].tangents, sizeof(unsigned int));
		//bitangents
		file.read((char*)&meshes[i].biTangents, sizeof(unsigned int));

		//vert Size
		file.read((char*)&meshes[i].numData, sizeof(unsigned int));
		//vert Data
		meshes[i].data = new float[meshes[i].numData];
		file.read((char*)&(*meshes[i].data), meshes[i].numData * sizeof(float));
		//ind Size
		file.read((char*)&meshes[i].numIndices, sizeof(unsigned int));
		//ind Data
		meshes[i].indices = new unsigned int[meshes[i].numIndices];
		file.read((char*)&(*meshes[i].indices), meshes[i].numIndices * sizeof(unsigned int));
	}

	// OGL part
	_mesh = new MeshOGL[_numMeshes];

	for (unsigned int i = 0; i != _numMeshes; ++i)
	{
		_mesh->numIndices = meshes[i].numIndices;

		glGenVertexArrays(1, &_mesh->VAO);
		glGenBuffers(1, &_mesh->VBO);
		glGenBuffers(1, &_mesh->EBO);

		glBindVertexArray(_mesh->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, meshes[i].numData * sizeof(float), meshes[i].data, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshes[i].numIndices * sizeof(unsigned int), meshes[i].indices, GL_STATIC_DRAW);

		// Position attribute //0, 1, 2
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute

		// UV attribute // 3, 4
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		// Normal attribute // 5, 6, 7
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);
		// Tangent attribute // 8, 9, 10
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(4);
		// Bitangent attribute // 11, 12, 13
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
		glEnableVertexAttribArray(5);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// release data
	delete[] meshes;
}

void Loader::LoadTxt(std::string _path, std::string& _str)
{
	std::ifstream file(_path);

	if (!file.is_open())
	{
		std::string str = "ERROR: Failed to open: \""; str += _path; str += "\";";
		Logger::Log(str);
		return;
	}

	_str = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
}
