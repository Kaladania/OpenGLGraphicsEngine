#include "Pyramid.h"

#include <iostream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Pyramid::Pyramid(Vector3D scale, float newTranslationSpeed, float newRotationSpeed, std::string choosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, choosenTexture)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	meshTextFileName = "Pyramid";
	textureFileName = choosenTexture;

	LoadVerticesFromFile();
	LoadTextureFromFile();
	//SetUpVertices(newVertexList);

	ScalePolygon(scale, indexedVertices);

}

/// <summary>
/// Constructor using a uniform float scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Pyramid::Pyramid(float scale, float newTranslationSpeed, float newRotationSpeed, std::string choosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, choosenTexture)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon

	meshTextFileName = "Pyramid";
	textureFileName = choosenTexture;

	LoadVerticesFromFile();
	LoadTextureFromFile();

	ScalePolygon(scale, indexedVertices);
}