#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <fstream>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

#include "Mesh.h"
#include "Model.h"

#include "MeshOGL.h"

class Loader
{
private:
	

public:
	void LoadOBJ(std::string _path, Mesh& _mesh);
	
	//void LoadBinaryMesh(std::string _path, MeshOGL*& _mesh, unsigned int& _numMeshes);
	void LoadBinaryMesh2(std::string _path, MeshOGL*& _mesh, unsigned int& _numMeshes);

	void LoadTxt(std::string _path, std::string& _str);
private:

};

#endif