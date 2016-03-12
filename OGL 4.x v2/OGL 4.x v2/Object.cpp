#include "Object.h"

Object::Object()
{
	mesh = nullptr;
	model = nullptr;
	shader = nullptr;
	diffuse = nullptr;
	normalMap = nullptr;

	objectMatrix.Translate(0.0f, 0.0f, -5.0f);
}

Object::~Object()
{

}

void Object::Draw()
{
	// bind
	if(mesh != nullptr)
		mesh->Bind();
	shader->Bind();
	if (diffuse != nullptr)
		diffuse->Bind(GL_TEXTURE0, shader->GetUniform("diffuseMap"),0);
	if(normalMap != nullptr)
		normalMap->Bind(GL_TEXTURE1, shader->GetUniform("normalMap"),1);

	objectMatrix.Bind(shader->GetUniform("modelMatrix"));

	// draw
	if (mesh != nullptr)
		mesh->Draw();
	//model->Draw();

	// unbind
	normalMap->UnBind();
	diffuse->UnBind();
	shader->UnBind();
	mesh->UnBind();
}
