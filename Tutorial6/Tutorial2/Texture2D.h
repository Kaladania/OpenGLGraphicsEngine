#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <string>
//#include <gl/GLU.h>
//#include "freeglut.h"
struct TexCoord
{
	GLfloat u = 0.0f;
	GLfloat v = 0.0f;
};
class Texture2D
{
private:
	GLuint textureID;
	int width = 0;
	int height = 0;
	char* textureData;
	//std::string textureName = "";

public:
	Texture2D();
	~Texture2D();

	bool LoadTexture(std::string path, const int width = 0, const int height = 0);
	bool LoadRAW(std::string path, const int width = 0, const int height = 0);
	bool LoadPNG(std::string path, const int width = 0, const int height = 0);

	GLuint GetID() const { return textureID; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height;  }

};

