#pragma once
#ifndef _POLYGON
#define _POLYGON

#include <array>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include "Header.h"
#include "Texture2D.h"

class Texture2D;

class Polygon3D
{
protected:
	int sides = 0;; //number of sides in polygon
	int vertexAmount = 0;; //number of vertices in polygon
	int indiciesAmount = 0;
	int textCoordAmount = 0;
	std::vector<Vector3D> vertexList; //polygon vertex locations
	//std::string textFileName = "";

	std::vector<Vector3D> indexedVertices;
	std::vector<Vector3D> indexedNormals;
	std::vector<int> indices;
	std::vector<TexCoord> indexedTextCoords;
	int textCoordIterator = 0;

	std::string meshTextFileName = ""; //name of txt file to pull vertices from
	std::string textureFileName = ""; //name of txt file to pull vertices from

	//std::vector<Texture2D*> textures;
	Texture2D* texture = nullptr;
	
	Vector3D rotationAxis = Vector3D(); //rotation vector
	Vector3D rotationDirection; //current rotation direction
	Vector3D translation = Vector3D(); //translation vector
	Vector3D scale = Vector3D(1.0f, 1.0f, 1.0f); //scale vector

	float rotationSpeed = 0; //speed of automatic rotation
	float rotation = 0; //current rotation
	float translationSpeed = 0; //speed of automatic translation

	enum Color; //forward declarion of enum color
	Color color = WHITE; //shape color

	std::array<float, 4> colorArray = { 1.0f, 1.0f, 1.0f, 0.0f }; //array holding the interger values for the enum colour

	bool switchDirection = false; //states wheither current rotation/translation should be inverted

	Material* material;

	
	//std::map <Textures, std::string> textureEnumToString;= { (PENGUINS, "Penguins"), (STARS, "Stars") };

public:
	

	Polygon3D(Vector3D scale = Vector3D(1, 1, 1), float newTranslationSpeed = 0, float newRotationSpeed = 0, std::string choosenTexture = "");
	Polygon3D(float scale = 1, float newTranslationSpeed = 0, float newRotationSpeed = 0, std::string choosenTexture = "");

	virtual void Draw();

	bool LoadVerticesFromFile();
	bool LoadOBJFromFile();
	bool LoadTextureFromFile();

	virtual void ScalePolygon(Vector3D scale, std::vector<Vector3D>& vertexList);
	virtual void ScalePolygon(float scale, std::vector<Vector3D>& vertexList);

	virtual void TranslatePolygon(Vector3D translationVector);
	int chosenTranslationAxis;

	virtual void RotatePolygon();
	int chosenRotationAxis;

	//Returns rotation direction
	Vector3D GetRotation()
	{
		return rotation;
	}

	//Updates rotation direction
	void SetRotation(Vector3D rotationAxis)
	{
		this->rotationAxis = rotationAxis;
	}

	//Updates rotation speed
	void SetRotationSpeed(float translationSpeed)
	{
		this->translationSpeed = translationSpeed;
	}

	//Returns rotation speed
	Vector3D GetRotationSpeed()
	{
		return rotationSpeed;
	}

	//Enum of current color options
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
