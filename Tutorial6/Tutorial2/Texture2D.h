#pragma once
#include <Windows.h>
#include "freeglut.h"
#include <string>

//Texture Co-ordinate Structure
struct TexCoord
{
	GLfloat u = 0.0f;
	GLfloat v = 0.0f;

	TexCoord(GLfloat u, GLfloat v)
	{
		this->u = u;
		this->v = v;
	}
	
};
class Texture2D
{
private:
	GLuint textureID = 0; //texture ID assigned by GLUT
	int width = 0; //texture width
	int height = 0; //texture heigh
	char* textureData = nullptr; //data read from texture file


public:
	Texture2D();
	~Texture2D();

	bool LoadTexture(std::string path, const int width = 0, const int height = 0);
	bool LoadRAW(std::string path, const int width = 0, const int height = 0);
	bool LoadPNG(std::string path, const int width = 0, const int height = 0);

	GLuint GetID() { return textureID; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height;  }

};

