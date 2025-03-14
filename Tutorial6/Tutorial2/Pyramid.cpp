#include "Pyramid.h"

#include <iostream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Pyramid::Pyramid(Vector3D scale, float newTranslationSpeed, float newRotationSpeed, Textures chosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, chosenTexture)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	meshTextFileName = "Pyramid";
	//textureFileName = choosenTexture;

	material->ambient = { 1.0f, 0.5f, 0.2f, 1.0f };
	material->diffuse = { 1.80f, 1.05f, 1.05f, 1.0f };
	material->specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material->shininess = 20.0f;

	LoadVerticesFromFile();
	LoadTextureFromFile(chosenTexture);
	//SetUpVertices(newVertexList);

	ScalePolygon(scale, indexedVertices);

}

/// <summary>
/// Constructor using a uniform float scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Pyramid::Pyramid(float scale, float newTranslationSpeed, float newRotationSpeed, Textures chosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, chosenTexture)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon

	meshTextFileName = "Pyramid";
	//textureFileName = choosenTexture;

	material->ambient = { 1.0f, 0.5f, 0.2f, 1.0f };
	material->diffuse = { 1.80f, 1.05f, 1.05f, 1.0f };
	material->specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material->shininess = 20.0f;

	LoadVerticesFromFile();
	LoadTextureFromFile(chosenTexture);

	ScalePolygon(scale, indexedVertices);
}