#ifndef WINDOWOGL4X_H
#define WINDOWOGL4X_H

#include <Windows.h>
#include "GL\glew.h"
#include "GL\wglew.h"
#include <iostream>

#include "Logger.h"

class WindowOGL4x
{
public:
	WindowOGL4x(char* _strGameName, char* _strWndClassName, int _x, int _y, unsigned int _width, unsigned int _height, unsigned int _majorOGLVersion, unsigned int _minorOGLVersion);
	~WindowOGL4x();

	MSG GetMSG(){ return msg; }
	HDC GetHDC(){ return hDC; }
	int GetX(){ return x; }
	int GetY(){ return y; }
	unsigned int GetWidth(){ return width; }
	unsigned int GetHeight(){ return height; }

	HDC hDC;
	HGLRC hRC;

private:
	char* strGameName;

	int x;
	int y;

	unsigned int width;
	unsigned int height;

	short glMajorVersion;
	short glMinorVersion;

	MSG msg;

	//

	HWND hWnd;
	HINSTANCE hInstance;
	DWORD wndStyle;


	char* strWndClassName;

	WindowOGL4x(){};
};

#endif