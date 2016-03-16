#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "assimpd.lib")

#include <crtdbg.h>
#include <Windows.h>

#include "Logger.h"
#include "WindowOGL4x.h"

#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Object.h"
#include "Camera.h"

#include "Light.h"

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

int main()
{
	//std::string str1 = "45";
	//std::string str2 = "3.14159";
	//std::string str3 = "31337 with words";
	//std::string str4 = "words and 2";
	//
	//int myint1;
	//std::stoi(str1, &myint1,10);
	//int myint2 = std::stoi(str2);
	//int myint3 = std::stoi(str3);



	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1181);

	MoveWindow(GetConsoleWindow(), 0, 0, 1024, 800, true);

	Logger::Clear();

	std::cout << "Use QWEASD UIOJKL and MOUSE to move the Camera, ZX to rotate directional light.\n\n";

	Logger::Log("STARTING PROGRAM;\n");

	//Window
	WindowOGL4x* window = new WindowOGL4x("Game Name", "A", 1124, 0, 1024, 720, 4, 5);

	Logger::Log("LOADING/COMPILING SHADERS");

	// InitGL
	glViewport(0, 0, window->GetWidth(), window->GetHeight());
	glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, window->GetWidth() / window->GetHeight(), 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	//glShadeModel(GL_FLAT);          // no color interpolation
	glShadeModel(GL_SMOOTH);        // color interpolation (default)
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	POINT mousePos, oldMousePos;
	SetCursorPos(300, 300);
	GetCursorPos(&oldMousePos);

	// SHADERS
	//Shader* shader = new Shader();
	//Shader* shaderExplodeMesh = new Shader("res/shaders/ExplodeMesh.vertexShader","res/shaders/ExplodeMesh.geometryShader","res/shaders/ExplodeMesh.fragmentShader");
	//Shader* shader = new Shader("res/shaders/Explode.vs","res/shaders/Explode.gs","res/shaders/Explode.fs");
	Shader* shader = new Shader("res/shaders/Lights.vs", "poop", "res/shaders/Lights.fs");
	

	//Model* icoSphereModel = new Model("IcoSphere.obj");
	//Model* hiPolyIcoSphereModel = new Model("hiPolyIcoSphere.obj");
	//Model* cubeMeshModel = new Model("res/cube.obj");
	
	// MESHES
	Mesh* mesh = new Mesh();
	Mesh* icoSphere = new Mesh("IcoSphere.obj");
	//Mesh* hiPolyIcoSphere = new Mesh("hiPolyIcoSphere.obj");
	Mesh* cubeMesh = new Mesh("res/cube.obj");

	// TEXTURES
	//Texture* texture = new Texture("abstract-colorful-clouds-2560x1600-wallpaper-16983.bmp");
	Texture* diffuseMap = new Texture("res/154.bmp");
	Texture* normalMap = new Texture("res/154_norm.bmp");
	Texture* cubeMap = new Texture("res/cube.bmp");
	
	//MODELS
	Model* monkey = new Model("res/monkey.model");
	monkey->shader = shader;
	monkey->diffuse = diffuseMap;
	monkey->normalMap = normalMap;
	monkey->objectMatrix.Translate(0.0f, 0.0f, -2.5f);

	// OBJECTS
	Object* cube = new Object();
	//cube->model = cubeMeshModel;
	cube->mesh = cubeMesh;
	cube->diffuse = cubeMap;
	cube->shader = shader;

	Object* object = new Object();
	//object->model = icoSphereModel;
	object->mesh = icoSphere;
	object->shader = shader;
	object->diffuse = diffuseMap;
	object->normalMap = normalMap;

	//Object* object2 = new Object();
	//object2->model = hiPolyIcoSphereModel;
	//object2->mesh = hiPolyIcoSphere;
	//object2->shader = shader;
	//object2->diffuse = diffuseMap;
	//object2->normalMap = normalMap;
	//object2->objectMatrix.Translate(0.0f, 2.0f, 0.0f);

	Object* floor = new Object();
//	floor->model = cubeMeshModel;
	floor->mesh = mesh;
	floor->shader = shader;
	floor->diffuse = diffuseMap;
	floor->normalMap = normalMap;
	floor->objectMatrix.Translate(0.0f, -2.0f, 0.0f);
	floor->objectMatrix.Rotate(90.0f/180.0f*3.141592f, 1.0f, 0.0f, 0.0f);
	floor->objectMatrix.Scale(5.0f, 0.1f, 5.0f);

	Matrix* projection = new Matrix();
	projection->SetProjection(45.0f, (float)window->GetWidth(), (float)window->GetHeight(), 0.1f, 100.0f);
	
	Camera* camera = new Camera();

	// LIGHT
	AmbientLight* aLight = new AmbientLight();
	aLight->SetColorRGB(0.025f, 0.025f, 0.025f);

	DirectionalLight* dLight = new DirectionalLight();
	dLight->SetOrientationXYZ(0.0f, -1.0f, 0.0f);
	dLight->SetColorRGB(0.5f, 0.5f, 0.5f);
	dLight->SetIntensityF(1.0f);

	PointLight* pLight = new PointLight();
	pLight->SetPositionXYZ(2.0f,1.0f,1.0f);
	pLight->SetColorRGB(0.0f, 0.0f, 1.0f);
	pLight->SetConstantF(1.0f);
	pLight->SetLinearF(0.09f);
	pLight->SetQuadraticF(0.032f);

	SpotLight* sLight = new SpotLight();
	sLight->SetPositionXYZ(-1.5f, 5.0f, -4.5f);
	sLight->SetColorRGB(1.0f,1.0f,1.0f);
	sLight->SetOrientationXYZ(0.0f, -1.0f, 0.0f);
	sLight->SetConstantF(1.0f);
	sLight->SetLinearF(0.09f);
	sLight->SetQuadraticF(0.032f);
	sLight->SetCutOffsFF(5.5f, 10.0f);

	// Loop
	for (;;)
	{
		//Manage Window
		if (PeekMessage(&window->GetMSG(), NULL, 0, 0, PM_REMOVE) == 0)
		{
			if (window->GetMSG().message == WM_QUIT)
				break;
			else
			{
				TranslateMessage(&window->GetMSG());
				DispatchMessage(&window->GetMSG());
			}
		}
		else
		{
			//Input
			if (GetAsyncKeyState(VK_ESCAPE))
				break;

			if (GetAsyncKeyState('W'))
				camera->MoveForwardLocal();
			if (GetAsyncKeyState('S'))
				camera->MoveBackwardLocal();
			if (GetAsyncKeyState('A'))
				camera->MoveLeftLocal();
			if (GetAsyncKeyState('D'))
				camera->MoveRightLocal();
			if (GetAsyncKeyState('Q'))
				camera->MoveDownLocal();
			if (GetAsyncKeyState('E'))
				camera->MoveUpLocal();

			if (GetAsyncKeyState('I'))
				camera->MoveForwardGlobal();
			if (GetAsyncKeyState('K'))
				camera->MoveBackwardGlobal();
			if (GetAsyncKeyState('J'))
				camera->MoveLeftGlobal();
			if (GetAsyncKeyState('L'))
				camera->MoveRightGlobal();
			if (GetAsyncKeyState('U'))
				camera->MoveDownGlobal();
			if (GetAsyncKeyState('O'))
				camera->MoveUpGlobal();

			static float dLightDir =  0.0f;
			
			if (GetAsyncKeyState('Z'))
				dLightDir -= 0.01f;
			if (GetAsyncKeyState('X'))
				dLightDir += 0.01f;
			
			dLight->SetOrientationXYZ(-sin(dLightDir), -cos(dLightDir), -0.3f);

			GetCursorPos(&mousePos);
			
			camera->RotateLocalX((mousePos.y - oldMousePos.y)*0.001f);
			camera->RotateGlobalY((mousePos.x - oldMousePos.x)*0.001f);

			SetCursorPos(300, 300);
			GetCursorPos(&oldMousePos);

			// update
			object->objectMatrix.Rotate(0.001f, 0.1f, 1.0f, 0.0f);
			pLight->SetPositionXYZ(camera->position.x, camera->position.y, camera->position.z);


			sLight->SetPositionXYZ(camera->position.x, camera->position.y, camera->position.z);
			glm::vec3 ori = camera->GetOrientationVector();
			sLight->SetOrientationXYZ(ori.x, ori.y, ori.z);

			// create matrix
			Matrix viewMatrix;
			viewMatrix.Multiply(projection->GetMatrix(), camera->getViewMatrix());

			//Render
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// bind
			shader->Bind();

			viewMatrix.Bind(shader->GetUniform("viewMatrix"));
			camera->Bind(shader->GetUniform("cameraPos"));

			aLight->Bind(shader->GetUniform("ambientLight"));
			dLight->Bind(shader->GetUniform("directionalLight"));
			pLight->Bind(shader->GetUniform("pointLight"));
			sLight->Bind(shader->GetUniform("spotLight"), shader->GetUniform("spotCutOffs"));
			
			// draw
			//object->Draw();
			//object2->Draw();
			floor->Draw();
			//cube->Draw();

			

			monkey->Draw();

			// unbind
			shader->UnBind();
			
			SwapBuffers(window->GetHDC());
		}
	}

	//lights
	delete sLight;
	delete aLight;
	delete dLight;
	delete pLight;

	//objects
	delete cube;
	delete floor;
	delete object;
	//delete object2;

	delete camera;
	delete projection;

	//textures
	delete normalMap;
	delete diffuseMap;
	delete cubeMap;

	//meshes
	delete cubeMesh;
	delete mesh;
	delete icoSphere;
	//delete hiPolyIcoSphere;

	// MODELS
	delete monkey;

	//shaders
	delete shader;
	
	delete window;
}

// REFERENCES
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
//http://learnopengl.com/#!Getting-started/Hello-Triangle
//http://learnopengl.com/#!Getting-started/Shaders
//http://learnopengl.com/#!Getting-started/Textures