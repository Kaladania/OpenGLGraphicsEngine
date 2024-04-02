#include "Polygon3D.h"
#include <iostream>

Polygon3D::Polygon3D(Vector3D scale, Vector3D rotationSpeed)
{
	//SetUpVertices();
}

Polygon3D::Polygon3D(float scale, Vector3D rotationSpeed)
{
	//SetUpVertices();
}

void Polygon3D::Draw()
{

}

void Polygon3D::SetUpVertices()
{

}

/// <summary>
/// Returns an array of color values
/// </summary>
/// <param name="color">The color being requested</param>
/// <param name="colorArray">Array of float values representing R, G, B and A</param>
void Polygon3D::SetColor(const Color color)
{
	this->color = color;
	switch (color)
	{
	case RED:
		colorArray[0] = 1.0f;
		colorArray[1] = 0.0f;
		colorArray[2] = 0.0f;
		colorArray[3] = 0.0f;
		break;

	case ORANGE:
		colorArray[0] = 1.0f;
		colorArray[1] = 0.5f;
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

/// <summary>
/// Scales the Polygon by the given vector
/// </summary>
/// <param name="scale">The scalar vector</param>
void Polygon3D::ScalePolygon(Vector3D scale, std::vector<Vector3D>& vertexList)
{
	for (int i = 0; i < vertexList.size(); i++)
	{
		vertexList[i] = vertexList[i] * scale;
		//printf("%f, %f, %f \n", vertexList[i].x, vertexList[i].y, vertexList[i].z);
	}
}

/// <summary>
/// Scales the Polygon by the given float
/// </summary>
/// <param name="scale">Scalar float</param>
void Polygon3D::ScalePolygon(float scale, std::vector<Vector3D>& vertexList)
{
	for (int i = 0; i < vertexList.size(); i++)
	{
		vertexList[i] = vertexList[i] * scale;
		//printf("%f, %f, %f \n", vertexList[i].x, vertexList[i].y, vertexList[i].z);
	}
}

void Polygon3D::TranslatePolygon(Vector3D translationVector)
{
	glTranslatef(0.0f, 0.0f, translationVector.z);

	if (translationVector.z > 300)
	{
		switchDirection = true;
	}
	else if (translationVector.z < -300)
	{
		switchDirection = false;
	}
	
}