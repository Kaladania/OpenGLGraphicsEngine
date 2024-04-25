#include "Cube.h"
#include <iostream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Cube::Cube(Vector3D scale, float newTranslationSpeed, float newRotationSpeed, std::string choosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, choosenTexture)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	meshTextFileName = "Cube";
	textureFileName = choosenTexture;
	
	LoadVerticesFromFile();
	LoadTextureFromFile();

	material.ambient = { 0.80f, 0.0f, 0.05f, 1.0f};
	material.diffuse = { 0.80f, 0.0f, 0.05f, 1.0f };
	material.specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.shininess = 100.0f;

	//SetUpVertices(newVertexList);

	ScalePolygon(scale, indexedVertices);

}

/// <summary>
/// Constructor using a uniform float scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Cube::Cube(float scale, float newTranslationSpeed, float newRotationSpeed, std::string choosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, choosenTexture)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	
	meshTextFileName = "Cube";
	textureFileName = choosenTexture;

	std::cout << "Rotation speed: " << translationSpeed << "\n";

	LoadVerticesFromFile();
	LoadTextureFromFile();

	ScalePolygon(scale, indexedVertices);
}


