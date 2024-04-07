#include "Cube.h"
#include <iostream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
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

/// <summary>
/// Constructor using a uniform float scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Cube::Cube(float scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	
	textFileName = "Cube";

	std::cout << "Rotation speed: " << translationSpeed << "\n";

	LoadVerticesFromFile();

	ScalePolygon(scale, vertexList);
}


