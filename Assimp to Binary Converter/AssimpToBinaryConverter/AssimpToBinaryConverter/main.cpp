#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "assimpd.lib")

#include "Model.h"

#include "Logger.h"

void GetTypedString(std::string& _str)
{
	for (;;)
	{
		system("cls");
		std::cout << _str;

		Sleep(100);

		if (GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_RETURN))
			break;

		if (GetAsyncKeyState(VK_BACK))
		{
			if (_str.size() > 0)
			{
				_str.pop_back();
			}
		}

		for (int i = 'A'; i != 'Z' + 1;++i)
		{
			if (!GetAsyncKeyState(VK_SHIFT))
			{
				if (GetAsyncKeyState(i))
				{
					_str.push_back((char)i+32);
				}
			}
			else
			{
				if (GetAsyncKeyState(i))
				{
					_str.push_back((char)i);
				}
			}
		}

		for (int i = '0'; i != '9' + 1;++i)
		{
			if (GetAsyncKeyState(i))
			{
				_str.push_back((char)i);
			}
		}

		if (GetAsyncKeyState(VK_SPACE))
			_str.push_back(' ');
		if (GetAsyncKeyState(VK_DIVIDE))
			_str.push_back('/');
		if (GetAsyncKeyState(VK_OEM_PLUS))
			_str.push_back('+');
		if (GetAsyncKeyState(VK_OEM_MINUS))
			_str.push_back('-');
		if (GetAsyncKeyState(VK_OEM_PERIOD))
			_str.push_back('.');
		if (GetAsyncKeyState(VK_OEM_2))
			_str.push_back('/');
		if (GetAsyncKeyState(VK_OEM_3))
			_str.push_back('~');
	}
}

void GetFilesInDirectory(std::vector<std::string> &out, std::string &directory)
{
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return; /* No files found */

	do {
		const std::string file_name = file_data.cFileName;
		const std::string full_file_name = directory + "/" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		int size = full_file_name.size();
		//skip .dll
		if(full_file_name[size - 1] == 'l' && full_file_name[size - 2] == 'l' && full_file_name[size - 3] == 'd' && full_file_name[size - 4] == '.')
			continue;

		//skip .exe
		if (full_file_name[size - 1] == 'e' && full_file_name[size - 2] == 'x' && full_file_name[size - 3] == 'e' && full_file_name[size - 4] == '.')
			continue;

		//skip .txt
		if (full_file_name[size - 1] == 't' && full_file_name[size - 2] == 'x' && full_file_name[size - 3] == 't' && full_file_name[size - 4] == '.')
			continue;

		out.push_back(full_file_name);
	} while (FindNextFile(dir, &file_data));

	FindClose(dir);
}

void RemoveDirectoryFromStr(std::string& _str)
{
	//find last slash
	int lastSlash = 0;
	for (int i = 0; _str[i] != '\0'; ++i)
	{
		if (_str[i] == '/' || _str[i] == '\\')
			lastSlash = i;
	}

	for (int i = 0; i != lastSlash+1; ++i)
	{
		_str.erase(0, 1);
	}
}

int main()
{
	Logger::Clear();

	std::string str = "What do you want to do?\n"
		"	1 -> Convert all files in this directory;\n"
		"	2 -> See how to load a file;\n"
		"	3 -> Convert a specific file;\n"
		"	4 -> Exit;\n";

	Logger::Log(str);

	int selection = 4;
	for (;;)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			Logger::Log("USER PRESSED ESC;");
			return 0;
		}
		else if (GetAsyncKeyState('1'))
		{
			selection = 1;
			break;
		}
		else if (GetAsyncKeyState('2'))
		{
			selection = 2;
			break;
		}
		else if (GetAsyncKeyState('3'))
		{
			selection = 3;
			break;
		}
		else if (GetAsyncKeyState('4'))
		{
			selection = 4;
			break;
		}
	}

	std::string str2 = "Selected ";
	str2 += (char)selection + '0';
	str2 += ';';

	Logger::Log(str2);

	std::vector<std::string> dir;
	char DefChar = ' ';
	HMODULE hModule = GetModuleHandleW(NULL);
	int charEnd;

	std::string directoryPath;
	std::string strDir;
	

	switch (selection)
	{
	case 1:
		Logger::Log("Looking for files;");
		//get path
		WCHAR wcPath[MAX_PATH];
		GetModuleFileNameW(hModule, wcPath, MAX_PATH);
		//convert path
		char chPath[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, wcPath, -1, chPath, 260, &DefChar, NULL);
		//store path
		directoryPath = chPath;
		//remove exe name
		charEnd = 0;
		for (int i = 0; directoryPath[i] != '\0'; ++i)
		{
			charEnd = i;
		}
		for (int i = charEnd; directoryPath[i] != '\\'; --i)
		{
			directoryPath.pop_back();
		}

		strDir = "Directory = \"";
		strDir += directoryPath;
		strDir += "\"\n";

		Logger::Log(strDir);

		GetFilesInDirectory(dir, directoryPath);

		for (int i = 0; i != dir.size(); ++i)
		{
			RemoveDirectoryFromStr(dir[i]);
		}

		break;
	case 2:
		system("cls");
		Logger::Log(
		"struct MeshData\n"
		"{\n"
		"	unsigned int dataType;\n"
		"\n"
		"	unsigned int numData;\n"
		"	float* data;\n"
		"\n"
		"	unsigned int numIndices;\n"
		"	unsigned int* indices;\n"
		"};\n"
		"\n// open file\n"
		"std::ifstream testFile(name, std::ifstream::binary);\n"
		"\n"
		"MeshData* mData;\n"
		"\n"
		"// get num meshes\n"
		"unsigned int numMesh;\n"
		"testFile.read((char*)&numMesh, sizeof(unsigned int));\n"
		"\n"
		"//create MeshData\n"
		"mData = new MeshData[numMesh];\n"
		"\n"
		"// for every mesh\n"
		"for (unsigned int i = 0; i != numMesh; ++i)\n"
		"{\n"
		"	// get mesh type\n"
		"	testFile.read((char*)&mData[i].dataType, sizeof(unsigned int));\n"
		"\n"
		"	// get mesh vertices size\n"
		"	testFile.read((char*)&mData[i].numData, sizeof(unsigned int));\n"
		"\n"
		"	// get mesh vertices\n"
		"	mData[i].data = new float[mData[i].numData];\n"
		"	testFile.read((char*)&(*mData[i].data), mData[i].numData * sizeof(float));\n"
		"\n"
		"	// get mesh indices size\n"
		"	testFile.read((char*)&mData[i].numIndices, sizeof(unsigned int));\n"
		"\n"
		"	// get mesh indices\n"
		"	mData[i].indices = new unsigned int[mData[i].numIndices];\n"
		"	testFile.read((char*)&*mData[i].indices, mData[i].numIndices * sizeof(GLuint));\n"
		"}\n");
		system("pause");
		return 0;
	case 3:
		Logger::Log("Please type the file name, if the file is not on the same directory as this .exe, add the directory;");
		dir.push_back(std::string());
		GetTypedString(dir[0]);
		break;
	case 4:
		Logger::Log("Exiting;");
		return 0;
		break;
	}

	system("cls");

	// loop tru strings load and write binary
	for (int i = 0; i != dir.size(); ++i)
	{
		std::string str = "\nLoading \""; str += dir[i];
		Logger::Log(str);
		Model* model = new Model(dir[i]);
		model->CreateBinaryFile();
		delete model;
	}

	system("pause");

	return 0;
}