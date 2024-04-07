#include "Cube.h"
#include <iostream>


Cube::Cube(Vector3D scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	textFileName = "Cube";
	
	LoadVerticesFromFile();
	//SetUpVertices(newVertexList);

	ScalePolygon(scale, vertexList);

}

Cube::Cube(float scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	
	textFileName = "Cube";

	std::cout << "Rotation speed: " << translationSpeed << "\n";

	LoadVerticesFromFile();

	ScalePolygon(scale, vertexList);
}


