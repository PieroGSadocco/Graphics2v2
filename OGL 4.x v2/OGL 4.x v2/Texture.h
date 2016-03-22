#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

class Texture
{
public:
	Texture(const char* _filename, GLuint _wrapping = GL_REPEAT, GLuint _minFilter = GL_LINEAR_MIPMAP_LINEAR, GLuint _magFilter = GL_LINEAR, bool _mipmap = true);
	~Texture();

	void Bind(GLint _GL_TEXTURENUM, GLint _uniformLocation, short _glTexNum);
	void UnBind();

	GLuint textureID;
private:
	/*
	First Parameter is the file location;
	Second is wrapping mode (GL_REPEAT(Default), GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER);
	Third and fourth is filtering mode (GL_LINEAR(Default Mag), GL_NEAREST, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR(Default Min));
	Fifth is mipmap, true by default
	*/
	bool loadBMP(const char* _filename, GLuint _wrapping = GL_REPEAT, GLuint _minFilter = GL_LINEAR_MIPMAP_LINEAR, GLuint _magFilter = GL_LINEAR, bool _mipmap = true);
	unsigned int width, height;
};

#endif