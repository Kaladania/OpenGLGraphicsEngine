#include "Teapot.h"


#include <iostream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Teapot::Teapot(Vector3D scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	meshTextFileName = "Teapot";
	textureFileName = "Penguin";

	LoadOBJFromFile();
	//SetUpVertices(newVertexList);

	ScalePolygon(scale, indexedVertices);

}

/// <summary>
/// Constructor using a uniform float scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Teapot::Teapot(float scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon

	meshTextFileName = "Teapot";
	textureFileName = "Penguin";

	LoadOBJFromFile();

	ScalePolygon(scale, indexedVertices);
}