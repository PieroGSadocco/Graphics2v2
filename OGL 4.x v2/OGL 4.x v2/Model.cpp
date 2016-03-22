#include "Model.h"

#include "Shader.h"

Model::Model(std::string _path)
{
	shader = nullptr;
	diffuse = nullptr;
	normalMap = nullptr;
	renderedMap = nullptr;

	numMeshes = 0;
	meshesOGL = nullptr;
	Loader loader;
	loader.LoadBinaryMesh2(_path, meshesOGL, numMeshes);
}

Model::~Model()
{
	for (int i = 0; i != numMeshes; ++i)
	{
		glDeleteVertexArrays(1, &meshesOGL[i].VAO);
		glDeleteBuffers(1, &meshesOGL[i].VBO);
		glDeleteBuffers(1, &meshesOGL[i].EBO);
	}

	delete[] meshesOGL;
}

void Model::Draw(Matrix* mat, Camera* cam)
{
	for (int i = 0; i != numMeshes; ++i)
	{
		// bind
		glBindVertexArray(meshesOGL[i].VAO);

		shader->Bind();
		mat->Bind(shader->GetUniform("viewMatrix"));
		cam->Bind(shader->GetUniform("cameraPos"));

		if (diffuse != nullptr)
			diffuse->Bind(GL_TEXTURE0, shader->GetUniform("diffuseMap"), 0);
		if (normalMap != nullptr)
			normalMap->Bind(GL_TEXTURE1, shader->GetUniform("normalMap"), 1);
		if (normalMap != nullptr)
			normalMap->Bind(GL_TEXTURE2, shader->GetUniform("renderedMap"), 2);
		
		objectMatrix.Bind(shader->GetUniform("modelMatrix"));

		static float explosionMagnitude = 0.0f;

		//if (GetAsyncKeyState('C'))
		//	explosionMagnitude -= 0.0002f;
		//if (GetAsyncKeyState('V'))
		//	explosionMagnitude += 0.0002f;
#include <Windows.h>

		explosionMagnitude = (1.0f + sin(GetTickCount()*0.001f));

		glUniform1f(shader->GetUniform("explosionMagnitude"), explosionMagnitude);

		// draw
		glDrawElements(GL_TRIANGLES, meshesOGL[i].numIndices, GL_UNSIGNED_INT, 0);

		// unbind
		normalMap->UnBind();
		diffuse->UnBind();
		shader->UnBind();

		
	}
}
