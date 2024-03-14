#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"
#include <array>


class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void); //class destructor

	void Display();

	enum colorCodes
	{
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		LIGHTBLUE,
		DARKBLUE,
		PURPLE,
		BLACK,
		WHITE

	};

	float SetColor(colorCodes color, std::array<float, 4>& colorArray);
	void DrawPolygon(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void DrawTriangle(std::array<float, 4>& colorCode, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

};

