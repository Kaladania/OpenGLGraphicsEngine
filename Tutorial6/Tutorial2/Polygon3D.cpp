#include "Polygon3D.h"
#include <iostream>
#include <fstream>

Polygon3D::Polygon3D(Vector3D scale, float newTranslationSpeed, float newRotationSpeed)
{
	//SetUpVertices();
	translationSpeed = newTranslationSpeed;
	rotationSpeed = newRotationSpeed;
}

Polygon3D::Polygon3D(float scale, float newTranslationSpeed, float newRotationSpeed)
{
	//SetUpVertices();
	translationSpeed = newTranslationSpeed;
	rotationSpeed = newRotationSpeed;

	LoadVerticesFromFile();
}

void Polygon3D::Draw()
{

	//glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	//glRotatef(10.0f, rotation.x, rotation.y, rotation.z); //rotates the drawn polygon

	//polygonRotation = polygonList[i]->GetRotation();
	printf("%f, %f, %f : %f \n", rotationAxis.x, rotationAxis.y, rotationAxis.z, rotationSpeed);


	//rotation = rotation + 0.1f;

	//glRotatef(rotationSpeed.z, 0.0f, 0.0f, 0.0f); //rotates the drawn polygon

	if (switchDirection)
	{
		translation = translation - translationSpeed;
		rotation = rotation - rotationSpeed;
	}
	else
	{
		translation = translation + translationSpeed;
		rotation = rotation + rotationSpeed;
	}



	switch (chosenTranslationAxis)
	{
	case(0):
		TranslatePolygon(Vector3D(translation.x, 0.0f, 0.0f));
		break;

	case(1):
		TranslatePolygon(Vector3D(0.0f, translation.y, 0.0f));
		break;

	case(2):
		TranslatePolygon(Vector3D(0.0f, 0.0f, translation.z));
		break;

	case(3):
		TranslatePolygon(Vector3D(translation.x, translation.y, 0.0f));
		break;

	case(4):
		TranslatePolygon(Vector3D(0.0f, translation.y, translation.z));
		break;

	case(5):
		TranslatePolygon(Vector3D(translation.x, 0.0f, translation.z));
		break;

	case(6):
		TranslatePolygon(Vector3D(translation.x, translation.y, translation.z));
		break;
	}




	switch (chosenRotationAxis)
	{
	case(0):
		rotationDirection = Vector3D(1.0f, 0.0f, 0.0f);
		break;

	case(1):
		rotationDirection = Vector3D(0.0f, 1.0f, 0.0f);
		break;

	case(2):
		rotationDirection = Vector3D(0.0f, 0.0f, 1.0f);
		break;

	case(3):
		rotationDirection = Vector3D(1.0f, 0.0f, 1.0f);
		break;

	case(4):
		rotationDirection = Vector3D(0.0f, 1.0f, 1.0f);
		break;

	case(5):
		rotationDirection = Vector3D(1.0f, 1.0f, 1.0f);
		break;

	case(6):
		rotationDirection = Vector3D(-1.0f, 0.0f, 0.0f);
		break;

	case(7):
		rotationDirection = Vector3D(0.0f, -1.0f, 0.0f);
		break;

	case(8):
		rotationDirection = Vector3D(0.0f, 0.0f, -1.0f);
		break;

	case(9):
		rotationDirection = Vector3D(-1.0f, 0.0f, -1.0f);
		break;

	case(10):
		rotationDirection = Vector3D(0.0f, -1.0f, -1.0f);
		break;

	case(11):
		rotationDirection = Vector3D(-1.0f, -1.0f, -1.0f);
		break;
	}

	RotatePolygon();
	//glRotatef(rotationSpeed, 0.0f, 0.0f, -0.1f);

	//glTranslatef(0.0f, 0.0f, rotation.z);


	int colorIterator = 0;
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < vertexList.size(); i++)
	{
		if (i % 3 == 0)
		{
			SetColor((Color)colorIterator);

			glColor4f(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);

			colorIterator++;

			if (colorIterator == BLACK)
			{
				colorIterator++;
			}

			if (colorIterator == END_OF_COLOR_ENUM)
			{
				colorIterator = 0;
			}
		}

		glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z);
	}

	glEnd();
	glPopMatrix();

}

bool Polygon3D::LoadVerticesFromFile()
{
	std::string filePath = "Cube.txt";

	std::ifstream inFile;

	inFile.open(filePath);

	if (!inFile.good())
	{
		std::cerr << "Can't open txt file:  " << filePath << std::endl;
		return false;
	}

	int x, y, z;
	char c;
	while ((inFile >> x >> y >> z))
	{
		vertexList.push_back(Vector3D(x, y, z));
		//printf(" %i, %i, %i", x, y, z);
	}
	
	inFile.close();

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
	glTranslatef(translationVector.x, translationVector.y, translationVector.z);

	if (translation > 0.5f && !switchDirection)
	{
		switchDirection = true;
		chosenTranslationAxis = rand() % 6;
	}
	else if (translation < -0.5f && switchDirection)
	{
		switchDirection = false;
		chosenTranslationAxis = rand() % 6;
	}
	
}


void Polygon3D::RotatePolygon()
{
	glRotatef(rotation, rotationDirection.x, rotationDirection.y, rotationDirection.z);

	if (rotation > 360.0f && !switchDirection)
	{
		switchDirection = true;
		chosenRotationAxis = rand() % 11;
	}
	else if (rotation < -360.0f && switchDirection)
	{
		switchDirection = false;
		chosenRotationAxis = rand() % 11;
	}

}