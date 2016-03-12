#include "WindowOGL4x.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



WindowOGL4x::WindowOGL4x(char* _strGameName, char* _strWndClassName, int _x, int _y, unsigned int _width, unsigned int _height, unsigned int _majorOGLVersion, unsigned int _minorOGLVersion)
{
	Logger::Log("OPENING WINDOW");

	strGameName = _strGameName;
	strWndClassName = _strWndClassName;

	x = _x;
	y = _y;
	width = _width;
	height = _height;

	glMajorVersion = _majorOGLVersion;
	glMinorVersion = _minorOGLVersion;

	hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wndClsEx;

	ZeroMemory(&wndClsEx, sizeof(WNDCLASSEX));
	wndClsEx.cbSize = sizeof(WNDCLASSEX);
	wndClsEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClsEx.lpfnWndProc = WindowProc;

	wndClsEx.cbClsExtra = 0;
	wndClsEx.cbWndExtra = 0;
	wndClsEx.hInstance = hInstance;
	wndClsEx.hIcon = NULL;
	wndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClsEx.hbrBackground = NULL;
	wndClsEx.lpszMenuName = NULL;
	wndClsEx.lpszClassName = TEXT(strWndClassName);
	wndClsEx.hIconSm = NULL;

	if (!RegisterClassEx(&wndClsEx))
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "!RegisterClassEx(&wndClsEx)");
	}

	DWORD m_unStyle = WS_OVERLAPPEDWINDOW;//WS_POPUP;
	DWORD m_unStyleX = NULL;

	hWnd = CreateWindowEx(m_unStyleX,
		wndClsEx.lpszClassName,
		strGameName,
		m_unStyle,
		x, y,
		width, height,
		NULL, NULL,
		hInstance,
		NULL);

	if (hWnd == NULL)
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "hWnd == NULL");
	}

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	hDC = GetDC(hWnd);
	SetPixelFormat(hDC, 1, &pfd);
	hRC = wglCreateContext(hDC);

	wglMakeCurrent(hDC, hRC);

	if (!hDC || !hRC)
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "\t\t!hDC || !hRC");
	}

	GLenum gleError = glewInit();

	if (gleError != GLEW_OK)
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "gleError != GLEW_OK");
	}

	const GLubyte *oglVersion = glGetString(GL_VERSION);

	Logger::Log(1, "Supported OpenGL Version:");
	Logger::Log(2, (char*)oglVersion);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);

	// Open a 2+.x GL window

	RECT rect;
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;

	AdjustWindowRectEx(&rect, m_unStyle, FALSE, m_unStyleX);

	int widthDiff = rect.right - rect.left - width;
	int heightDiff = rect.bottom - rect.top - height;

	hWnd = CreateWindowEx(m_unStyleX,
		wndClsEx.lpszClassName,
		strGameName,
		m_unStyle,
		x, y,
		width+widthDiff, height+heightDiff,
		NULL, NULL,
		hInstance,
		NULL);

	hDC = GetDC(hWnd);

	int nPixCount = 0;

	int pixAttribs[] = { WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering
		WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB, // must be HW accelerated
		WGL_COLOR_BITS_ARB, 32, // 8 bits of each R, G and B
		WGL_DEPTH_BITS_ARB, 16, // 16 bits of depth precision for window
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE, // Double buffered context
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, // MSAA on
		WGL_SAMPLES_ARB, 8, // 8x MSAA 
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, // pf should be RGBA type
		0 }; // NULL termination

	pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = -1;

	wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, &nPixelFormat, (UINT*)&nPixCount);

	if (nPixelFormat == -1)
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "!!! An error occurred trying to find a MSAA pixel format with the requested attribs.");

		pixAttribs[15] = 1;

		wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, &nPixelFormat, (UINT*)&nPixCount);

		if (nPixelFormat == -1)
		{
			// Couldn't find a format, perhaps no 3D HW or drivers are installed
			hDC = NULL;
			hRC = NULL;
			Logger::Log(1, "!!! An error occured creating an OpenGL window.");
			Logger::Log(2, "!!! An error occurred trying to find a pixel format with the requested attribs (2).");
		}
	}

	if (nPixelFormat != -1)
	{
		// Check for MSAA
		int attrib[] = { WGL_SAMPLES_ARB };
		int nResults = 0;
		wglGetPixelFormatAttribivARB(hDC, nPixelFormat, 0, 1, attrib, &nResults);

		Logger::Log(1, "Chosen pixel format is MSAA with num samples:");
		Logger::Log(2, nResults);

		// Got a format, now set it as the current one
		SetPixelFormat(hDC, nPixelFormat, &pfd);

		GLint attribs[5];

		if (glMajorVersion == 0 || glMajorVersion >= 5)
		{
			attribs[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
			attribs[1] = 4;
			attribs[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
			attribs[3] = 5;
			attribs[4] = 0;
		}
		else
		{
			attribs[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
			attribs[1] = glMajorVersion;
			attribs[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
			attribs[3] = glMinorVersion;
			attribs[4] = 0;
		}

		hRC = wglCreateContextAttribsARB(hDC, 0, attribs);
		while (hRC == NULL && attribs[1] != 0)
		{
			Logger::Log(1, "Could not create an OpenGL context:");
			std::string str(""); str += std::to_string(attribs[1]); str += '.'; str += std::to_string(attribs[3]);
			Logger::Log(2, str);

			attribs[3] = attribs[3] - 1;

			if (attribs[3] == -1)
			{
				attribs[1] = attribs[1] - 1;

				if (attribs[1] == 3)
					attribs[3] = 3;
				else if (attribs[1] == 2)
					attribs[3] = 1;
				else if (attribs[1] == 1)
					attribs[3] = 5;
			}

			hRC = wglCreateContextAttribsARB(hDC, 0, attribs);
		}

		glMajorVersion = attribs[1];
		glMinorVersion = attribs[3];

		Logger::Log(1, "Created an OpenGL context:");
		std::string str(""); str += std::to_string(glMajorVersion); str += '.'; str += std::to_string(glMinorVersion);
		Logger::Log(2, str);

		wglMakeCurrent(hDC, hRC);
	}

	if (!hDC)
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "!hDC");
	}

	if (!hRC)
	{
		Logger::Log(1, "!!! An error occured creating an OpenGL window.");
		Logger::Log(2, "!hRC");
	}

	Logger::Log(1, "Created an WindowOGL with context:");
	std::string str(""); str += std::to_string(glMajorVersion); str += '.'; str += std::to_string(glMinorVersion);
	Logger::Log(2, str);

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	str = std::string(""); str += "Maximum number of 4-component vertex attributes supported: "; str += std::to_string(nrAttributes);
	Logger::Log(1, str);


	// Show Window
	ShowWindow(hWnd, SW_NORMAL);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	//ShowCursor(false);
	Logger::Log("WINDOW OPENING COMPLETE\n");
}

WindowOGL4x::~WindowOGL4x()
{
	if (hRC)
	{
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		hRC = NULL;
	}

	if (hDC)
	{
		ReleaseDC(hWnd, hDC);
		hDC = NULL;
	}

	if (hWnd)
	{
		DestroyWindow(hWnd);
		hWnd = NULL;
	}

	UnregisterClass(strWndClassName, hInstance);
	hInstance = NULL;

	//UnregisterClass(L"DirectXApplication", application);

	Logger::Log("CLOSING WINDOW");
}

// Credits to Christian De La Paz for helping me with this several months ago.