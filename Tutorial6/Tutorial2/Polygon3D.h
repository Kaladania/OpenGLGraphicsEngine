#pragma once
#ifndef _POLYGON
#define _POLYGON

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"

#include <array>
#include <vector>
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

	Vector3D operator * (Vector3D scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x * scale.x;
		temp.y = this->y * scale.y;
		temp.z = this->z * scale.z;

		return temp;
	}

	Vector3D operator * (float scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x * scale;
		temp.y = this->y * scale;
		temp.z = this->z * scale;

		return temp;
	}



	Vector3D operator + (Vector3D scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x + scale.x;
		temp.y = this->y + scale.y;
		temp.z = this->z + scale.z;

		return temp;
	}

	Vector3D operator + (float scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x + scale;
		temp.y = this->y + scale;
		temp.z = this->z + scale;

		return temp;
	}


	Vector3D operator - (Vector3D scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x - scale.x;
		temp.y = this->y - scale.y;
		temp.z = this->z - scale.z;

		return temp;
	}

	Vector3D operator - (float scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x - scale;
		temp.y = this->y - scale;
		temp.z = this->z - scale;

		return temp;
	}


	bool operator > (Vector3D scale)
	{
		return (this->x > scale.x && this->y > scale.y && this->z > scale.z);
	}

	bool operator > (float scale)
	{

		return (this->x > scale && this->y > scale && this->z > scale);
	}


	bool operator < (Vector3D scale)
	{
		return (this->x < scale.x && this->y < scale.y && this->z < scale.z);
	}

	bool operator < (float scale)
	{

		return (this->x < scale && this->y < scale && this->z < scale);
	}
};




class Polygon3D
{
protected:
	int sides; //number of sides in polygon
	int vertexAmount; //number of vertices in polygon
	std::vector<Vector3D> vertexList; //polygon vertex locations
	
	Vector3D rotationAxis = Vector3D(); //rotation vector
	Vector3D rotationDirection;
	Vector3D translation = Vector3D(); //translation vector
	Vector3D scale = Vector3D(1.0f, 1.0f, 1.0f); //scale vector

	float rotationSpeed = 0; //speed of automatic rotation
	float rotation = 0;
	float translationSpeed = 0;

	enum Color; //forward declarion of enum color
	Color color = WHITE; //shape color

	std::array<float, 4> colorArray = { 1.0f, 1.0f, 1.0f, 0.0f }; //array holding the interger values for the enum colour

	bool switchDirection = false;

public:
	Polygon3D(Vector3D scale = Vector3D(1, 1, 1), float newTranslationSpeed = 0, float newRotationSpeed = 0);
	Polygon3D(float scale = 1, float newTranslationSpeed = 0, float newRotationSpeed = 0);

	virtual void Draw();
	virtual void SetUpVertices();
	virtual void ScalePolygon(Vector3D scale, std::vector<Vector3D>& vertexList);
	virtual void ScalePolygon(float scale, std::vector<Vector3D>& vertexList);

	virtual void TranslatePolygon(Vector3D translationVector);
	int chosenTranslationAxis;

	virtual void RotatePolygon();
	int chosenRotationAxis;

	Vector3D GetRotation()
	{
		return rotation;
	}

	void SetRotation(Vector3D rotationAxis)
	{
		this->rotationAxis = rotationAxis;
	}

	void SetRotationSpeed(float translationSpeed)
	{
		this->translationSpeed = translationSpeed;
	}

	Vector3D GetRotationSpeed()
	{
		return rotationSpeed;
	}

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
		WHITE,
		END_OF_COLOR_ENUM

	};


	
	void SetColor(const Color color);
};

#endif // !_POLYGON
