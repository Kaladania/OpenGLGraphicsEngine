#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"
#include <array>
#include <tuple>

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void); //class destructor

	void Display();

	std::array<float, 4> colorCode = { 1.0f, 0.0f, 0.0f, 0.0f }; //Array of RGBA values for current color
	std::tuple<float, float> vertex1; //position of 1st vertex of triangle
	std::tuple<float, float> vertex2; //position of 2nd vertex of triangle
	std::tuple<float, float> vertex3; //position of 3rd vertex of triangle
	std::tuple<float, float> point4;  //position of 4th vertex of triangle

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

	void SetColor(colorCodes color, std::array<float, 4>& colorArray);
	void DrawPolygon(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void DrawFreeTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3);
	void DrawEqualTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength);
	void DrawRightTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength);
	void DrawIsoTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength, const float bottomLength);

	void DrawEqualPolygon(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const int numberOfSides, const float sideLength);
};

