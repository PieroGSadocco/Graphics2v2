#include "Texture.h"

#include "Logger.h"

Texture::Texture(char* _filename, GLuint _wrapping, GLuint _minFilter, GLuint _magFilter, bool _mipmap)
{
	loadBMP(_filename);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Texture::Bind(GLint _GL_TEXTURENUM, GLint _uniformLocation, short _glTexNum)
{
	glActiveTexture(_GL_TEXTURENUM);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(_uniformLocation, _glTexNum);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadBMP(const char* _filename, GLuint _wrapping, GLuint _minFilter, GLuint _magFilter, bool _mipmap)
{
	unsigned char header[54];
	unsigned int dataPos;
	//unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	std::string str = "";

	FILE * file = fopen(_filename, "rb");
	if (!file)
	{
		str += "ERROR: Texture BMP: \""; str += _filename; str += "\"Not found.";
		Logger::Log(str);
		return;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		str += "ERROR:\nTexture BMP:\""; str += _filename; str += "\"Invalid (fread != 54).";
		Logger::Log(str);
		return;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		str += "ERROR:Texture BMP:\""; str += _filename; str += "\"Invalid (header[0] != 'B' [1] != 'M').";
		Logger::Log(str);
		return;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0) imageSize = width*height * 3;
	if (dataPos == 0) dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	// OGL part
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
	if (_mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;

	str = ""; str += "Texture BMP: \""; str += _filename; str += "\" Loaded Properly.\n";
	Logger::Log(str);
}