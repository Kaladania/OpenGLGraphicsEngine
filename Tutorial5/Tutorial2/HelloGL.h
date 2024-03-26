#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"
#include <array>
#include <tuple>
//#define REFRESH_RATE 16
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

class HelloGL
{
private:

	int refreshRate = 16; //current scene refresh rate
	float polygonRotation = 0.0f;//current polygon rotation
	float polygonRotationSpeed = 0.7f;
	float triangleRotation = 0.0f;

	std::array<float, 4> colorCode = { 1.0f, 0.0f, 0.0f, 0.0f }; //Array of RGBA values for current color
	std::tuple<float, float> vertex1; //position of 1st vertex of triangle
	std::tuple<float, float> vertex2; //position of 2nd vertex of triangle
	std::tuple<float, float> vertex3; //position of 3rd vertex of triangle
	std::tuple<float, float> vertex4;  //position of 4th vertex of triangle

	std::tuple<float, float, float> rotationAxis = std::make_tuple(0.0f, 0.0f, -1.0f);
	std::tuple<float, float, float> translationAxis = std::make_tuple(0.0f, 0.0f, 0.0f);

public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void); //class destructor

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
	void DrawQuadrilateral(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3, const std::tuple<float, float>& vertex4);
	void DrawFreeTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3);
	void DrawEqualTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength);
	void DrawRightTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength);
	void DrawIsoTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength, const float bottomLength);

	void DrawEqualPolygon(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const int numberOfSides, const float sideLength, const std::tuple<float, float, float>& rotationAxis, const float rotationSpeed);

	void Draw3D();
	void Display();
	void Update();

	void Keyboard(unsigned char key, int x, int y);
	float UpdateRotation(float rotation, float rotationSpeed);
};

