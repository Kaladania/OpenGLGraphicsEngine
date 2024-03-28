#pragma once
#ifndef _POLYGON
#define _POLYGON
#include <array>
#include <tuple>
//#include "Header.h"

struct Vector3D
{
	union { //allows iterative access to axises
		struct {
			float x; //rotation on x axis
			float y; //rotation on y axis
			float z; //rotation on z axis
		};
		float axis[3];
	};

	/// <summary>
	/// Constructor (defaults to 0 if axis value is not given)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector3D(float x = 0, float y = 0, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};




class Polygon
{
private:
	int sides; //number of sides in polygon
	int vertexAmount; //number of vertices in polygon
	std::array<Vector3D, 1> vertices; //polygon vertex locations
	
	Vector3D rotation; //rotation vector
	Vector3D translation; //translation vector
	Vector3D scale; //scale vector

	enum Color; //forward declarion of enum color
	Color color = WHITE; //shape color

public:
	Polygon(int sides, int vertices);

	virtual void Draw();
	virtual void AddVertices();

	enum Color
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


	/// <summary>
	/// Returns an array of color values
	/// </summary>
	/// <param name="color">The color being requested</param>
	/// <param name="colorArray">Array of float values representing R, G, B and A</param>
	void SetColor(const Color color, std::array<float, 4>& colorArray)
	{
		switch (color)
		{
		case RED:
			colorArray[0] = 1.0f;
			colorArray[1] = 0.0f;
			colorArray[2] = 0.0f;
			colorArray[3] = 0.0f;
			break;

		case YELLOW:
			colorArray[0] = 1.0f;
			colorArray[1] = 1.0f;
			colorArray[2] = 0.0f;
			colorArray[3] = 0.0f;
			break;

		case GREEN:
			colorArray[0] = 0.0f;
			colorArray[1] = 1.0f;
			colorArray[2] = 0.0f;
			colorArray[3] = 0.0f;
			break;

		case LIGHTBLUE:
			colorArray[0] = 0.0f;
			colorArray[1] = 1.0f;
			colorArray[2] = 1.0f;
			colorArray[3] = 1.0f;
			break;

		case DARKBLUE:
			colorArray[0] = 0.0f;
			colorArray[1] = 0.0f;
			colorArray[2] = 1.0f;
			colorArray[3] = 0.0f;
			break;

		case PURPLE:
			colorArray[0] = 1.0f;
			colorArray[1] = 0.0f;
			colorArray[2] = 1.0f;
			colorArray[3] = 0.0f;
			break;

		case BLACK:
			colorArray[0] = 0.0f;
			colorArray[1] = 0.0f;
			colorArray[2] = 0.0f;
			colorArray[3] = 0.0f;
			break;

		case WHITE:
			colorArray[0] = 1.0f;
			colorArray[1] = 1.0f;
			colorArray[2] = 1.0f;
			colorArray[3] = 0.0f;
			break;

		default: //returns white if current color is not supported
			colorArray[0] = 1.0f;
			colorArray[1] = 1.0f;
			colorArray[2] = 1.0f;
			colorArray[3] = 0.0f;
			break;
		}
	}
};

#endif // !_POLYGON
