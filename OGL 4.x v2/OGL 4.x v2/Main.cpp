#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "assimpd.lib")

#include <thread> 

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

#include "LightManager.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

void loadTexture(HDC hDC, HGLRC mainContext, Texture** tex, std::string _path)
{
	HGLRC hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	BOOL error = wglShareLists(mainContext, hRC);
	if (error == FALSE)
	{
		DWORD errorCode = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		//Destroy the GL context and just use 1 GL context
		wglDeleteContext(hRC);
	}
	*tex = new Texture(_path.c_str());
	wglMakeCurrent(hDC, NULL);
}

void loadShader(HDC hDC, HGLRC mainContext, Shader** shad, std::string _pathvs, std::string _pathgs, std::string _pathfs)
{
	HGLRC hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	BOOL error = wglShareLists(mainContext, hRC);
	if (error == FALSE)
	{
		DWORD errorCode = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		//Destroy the GL context and just use 1 GL context
		wglDeleteContext(hRC);
	}
	*shad = new Shader(_pathvs, _pathgs, _pathfs);
	wglMakeCurrent(hDC, NULL);
}



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1532);

	MoveWindow(GetConsoleWindow(), 0, 0, 1024, 800, true);

	Logger::Clear();

	std::cout << "Use QWEASD UIOJKL and MOUSE to move the Camera, ZX to rotate directional light.\n\n";

	Logger::Log("STARTING PROGRAM;\n");

	//Window
	WindowOGL4x* window = new WindowOGL4x("Game Name", "A", 1124, 0, 1024, 720, 4, 5);

	Logger::Log("LOADING/COMPILING SHADERS");

	Texture* diffuseMap;
	Texture* normalMap;
	Texture* cubeMap;

	Mesh* mesh = new Mesh();
	Mesh* cubeMesh = new Mesh("res/cube.obj");

	Shader* lightShader;// = new Shader("res/shaders/Lights.vs", "", "res/shaders/Lights.fs");
	Shader* explodeShader;// = new Shader("res/shaders/Explode.vs", "res/shaders/Explode.gs", "res/shaders/Explode.fs");
	Shader* skyboxShader;// = new Shader("res/shaders/Skybox.vs", "empty", "res/shaders/Skybox.fs");



	wglMakeCurrent(window->hDC, NULL); // thanks microsoft
	std::thread t_empty1(loadTexture, window->hDC, window->hRC, &diffuseMap, "res/154.bmp");
	while (t_empty1.joinable())
		t_empty1.join();
	wglMakeCurrent(window->hDC, NULL); // thanks microsoft
	std::thread t_empty2(loadTexture, window->hDC, window->hRC, &normalMap, "res/154_norm.bmp");
	while (t_empty2.joinable())
		t_empty2.join();
	wglMakeCurrent(window->hDC, NULL); // thanks microsoft
	std::thread t_empty3(loadTexture, window->hDC, window->hRC, &cubeMap, "res/cube.bmp");
	while (t_empty3.joinable())
		t_empty3.join();



	wglMakeCurrent(window->hDC, NULL); // thanks microsoft
	std::thread t_empty4(loadShader, window->hDC, window->hRC, &lightShader, "res/shaders/Lights.vs", "", "res/shaders/Lights.fs");
	while (t_empty4.joinable())
		t_empty4.join();
	wglMakeCurrent(window->hDC, NULL); // thanks microsoft
	std::thread t_empty5(loadShader, window->hDC, window->hRC, &explodeShader, "res/shaders/Explode.vs", "res/shaders/Explode.gs", "res/shaders/Explode.fs");
	while (t_empty5.joinable())
		t_empty5.join();
	wglMakeCurrent(window->hDC, NULL); // thanks microsoft
	std::thread t_empty6(loadShader, window->hDC, window->hRC, &skyboxShader, "res/shaders/Skybox.vs", "empty", "res/shaders/Skybox.fs");
	while (t_empty6.joinable())
		t_empty6.join();

	wglMakeCurrent(window->hDC, window->hRC);










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
	

	// MESHES
	

	// TEXTURES
	

	//MODELS
	Model* monkey = new Model("res/monkey.model");
	monkey->shader = lightShader;
	monkey->diffuse = diffuseMap;
	monkey->normalMap = normalMap;
	monkey->objectMatrix.Translate(0.0f, 0.0f, -2.5f);
	
	Model* skybox = new Model("res/models/skybox.model");
	skybox->shader = skyboxShader;
	skybox->diffuse = cubeMap;
	
	// OBJECTS
	Object* cube = new Object();
	cube->mesh = cubeMesh;
	cube->diffuse = cubeMap;
	cube->shader = skyboxShader;

	Matrix* projection = new Matrix();
	projection->SetProjection(45.0f, (float)window->GetWidth(), (float)window->GetHeight(), 0.1f, 100.0f);

	Camera* camera = new Camera();
	Camera* skyboxCamera = new Camera();

	// LIGHT
	LightManager* lightManager = new LightManager(10);	

	AmbientLight* aLight = new AmbientLight();
	aLight->SetColorRGB(0.025f, 0.025f, 0.025f);

	DirectionalLight* dLight = new DirectionalLight();
	dLight->SetOrientationXYZ(0.0f, -1.0f, 0.0f);
	dLight->SetColorRGB(0.7f, 0.7f, 0.7f);
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

	//const unsigned int ambLightIndex = 0;
	//const unsigned int dirLightIndex = 1;
	//
	//// AMBIENT
	//GLuint uniformBlockIndex = glGetUniformBlockIndex(shader->GetShaderProgram(), "ambientLights");
	//glUniformBlockBinding(shader->GetShaderProgram(), uniformBlockIndex, ambLightIndex);
	// 
	//float amb3[] = { 3.0f,0.0f,0.0f,0.0f,	
	//	0.2f,0.0f,0.0f,0.0f,
	//	0.0f,0.2f,0.0f,0.0f,
	//	0.0f,0.0f,0.2f,0.0f};
	//GLuint uboAmbientLights;
	//glGenBuffers(1, &uboAmbientLights);
	//glBindBuffer(GL_UNIFORM_BUFFER, uboAmbientLights);
	//glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(amb3), NULL, GL_STATIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//
	//glBindBufferRange(GL_UNIFORM_BUFFER, ambLightIndex, uboAmbientLights, 0, 1 * sizeof(amb3));
	//
	//glBindBuffer(GL_UNIFORM_BUFFER, uboAmbientLights);
	//glBufferSubData(GL_UNIFORM_BUFFER, 0, 1 * sizeof(amb3), &amb3);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//
	//// DIRECTIONAL
	//GLuint uniformBlockIndex2 = glGetUniformBlockIndex(shader->GetShaderProgram(), "DirectionalLights");
	//glUniformBlockBinding(shader->GetShaderProgram(), uniformBlockIndex2, dirLightIndex);
	//
	//float dir3[] = { 3.0f,0.0f,0.0f,0.0f,
	//	0.2f,0.0f,0.0f,0.0f,
	//	0.0f,0.2f,0.0f,0.0f,
	//	0.0f,0.0f,0.2f,0.0f };
	//GLuint uboDirectionalLights;
	//glGenBuffers(1, &uboDirectionalLights);
	//glBindBuffer(GL_UNIFORM_BUFFER, uboDirectionalLights);
	//glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(dir3), NULL, GL_STATIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//
	//glBindBufferRange(GL_UNIFORM_BUFFER, dirLightIndex, uboDirectionalLights, 0, 1 * sizeof(dir3));
	//
	//glBindBuffer(GL_UNIFORM_BUFFER, uboDirectionalLights);
	//glBufferSubData(GL_UNIFORM_BUFFER, 0, 1 * sizeof(dir3), &dir3);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

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
			dLightDir += 0.001f;
			
			dLight->SetOrientationXYZ(-sin(dLightDir), -cos(dLightDir), -0.3f);

			GetCursorPos(&mousePos);

			camera->RotateLocalX((mousePos.y - oldMousePos.y)*0.001f);
			camera->RotateGlobalY((mousePos.x - oldMousePos.x)*0.001f);
			skyboxCamera->RotateLocalX((mousePos.y - oldMousePos.y)*0.001f);
			skyboxCamera->RotateGlobalY((mousePos.x - oldMousePos.x)*0.001f);

			SetCursorPos(300, 300);
			GetCursorPos(&oldMousePos);

			// update
			pLight->SetPositionXYZ(camera->position.x, camera->position.y, camera->position.z);


			sLight->SetPositionXYZ(camera->position.x, camera->position.y, camera->position.z);
			glm::vec3 ori = camera->GetOrientationVector();
			sLight->SetOrientationXYZ(ori.x, ori.y, ori.z);

			// create matrix
			Matrix viewMatrix;

			//Render
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


			// bind
			lightShader->Bind();

			viewMatrix.Bind(lightShader->GetUniform("viewMatrix"));
			//projection->Bind(shader->GetUniform("viewMatrix"));

			lightManager->Bind(
				lightShader->GetShaderProgram(),
				lightShader->GetUniform("Lights"),
				lightShader->GetUniform("directionalLight_data"),
				lightShader->GetUniform("pointLight_data"),
				lightShader->GetUniform("spotLight_data"));

			aLight->Bind(lightShader->GetUniform("ambientLight"));
			dLight->Bind(lightShader->GetUniform("directionalLight"));
			pLight->Bind(lightShader->GetUniform("pointLight"));
			sLight->Bind(lightShader->GetUniform("spotLight"), lightShader->GetUniform("spotCutOffs"));
			
			// draw
			viewMatrix.Multiply(projection->GetMatrix(), skyboxCamera->getViewMatrix());
			skybox->objectMatrix.Scale(-1.0f, -1.0f, -1.0f);
			skybox->Draw(&viewMatrix, camera);
			skybox->objectMatrix.Scale(-1.0f, -1.0f, -1.0f);
			glClear(GL_DEPTH_BUFFER_BIT);
			viewMatrix.Multiply(projection->GetMatrix(), camera->getViewMatrix());

			// all lights
			monkey->objectMatrix.Translate(-3.0f, 0.0f, 0.0f);
			monkey->shader = lightShader;
			monkey->Draw(&viewMatrix, camera);
			// explode
			monkey->objectMatrix.Translate(+3.0f, 0.0f, 0.0f);
			monkey->shader = explodeShader;
			monkey->Draw(&viewMatrix, camera);
			// skybox
			monkey->objectMatrix.Translate(+3.0f, 0.0f, 0.0f);
			monkey->shader = skyboxShader;
			monkey->Draw(&viewMatrix, camera);

			monkey->objectMatrix.Translate(-3.0f, 0.0f, 0.0f);

			skybox->diffuse = diffuseMap;
			skybox->shader = lightShader;
			skybox->objectMatrix.Translate(0.0f, 0.0f, -4.0f);
			skybox->Draw(&viewMatrix, camera);
			skybox->diffuse = cubeMap;
			skybox->shader = skyboxShader;
			skybox->objectMatrix.Translate(0.0f, 0.0f, +4.0f);

			// unbind
			lightShader->UnBind();

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, 1024, 768);
			
			SwapBuffers(window->GetHDC());
		}
	}

	//lights
	delete sLight;
	delete aLight;
	delete dLight;
	delete pLight;

	delete lightManager;

	//objects
	delete cube;

	delete camera;
	delete skyboxCamera;
	delete projection;

	//textures
	delete normalMap;
	delete diffuseMap;
	delete cubeMap;

	//meshes
	delete cubeMesh;
	delete mesh;
	//delete hiPolyIcoSphere;

	// MODELS
	delete monkey;
	delete skybox;

	//shaders
	delete lightShader;
	delete explodeShader;
	delete skyboxShader;
	
	delete window;
}

// REFERENCES
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
//http://learnopengl.com/#!Getting-started/Hello-Triangle
//http://learnopengl.com/#!Getting-started/Shaders
//http://learnopengl.com/#!Getting-started/Textures