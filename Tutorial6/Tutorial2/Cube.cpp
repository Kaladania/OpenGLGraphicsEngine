#include "Cube.h"
#include <iostream>


Cube::Cube(Vector3D scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	ScalePolygon(scale, vertexList);

}

Cube::Cube(float scale, float newTranslationSpeed, float newRotationSpeed) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	

	std::cout << "Rotation speed: " << translationSpeed << "\n";

	ScalePolygon(scale, vertexList);
}

void Cube::Draw()
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


void Cube::SetUpVertices()
{
	// face v0-v1-v2

	std::array<Vector3D, 36> vertices = {
		Vector3D(1,1,1), Vector3D(-1, 1, 1), Vector3D(-1, -1, 1),
		Vector3D(-1, -1, 1), Vector3D(1, -1, 1), Vector3D(1, 1, 1),
		Vector3D(1, 1, 1), Vector3D(1, -1, 1), Vector3D(1, -1, -1),
		Vector3D(1, -1, -1), Vector3D(1, 1, -1), Vector3D(1, 1, 1),
		Vector3D(1, 1, 1), Vector3D(1, 1, -1), Vector3D(-1, 1, -1),
		Vector3D(-1, 1, -1), Vector3D(-1, 1, 1), Vector3D(1, 1, 1),
		Vector3D(-1, 1, 1), Vector3D(-1, 1, -1), Vector3D(-1, -1, -1),
		Vector3D(-1, -1, -1), Vector3D(-1, -1, 1), Vector3D(-1, 1, 1),
		Vector3D(-1, -1, -1), Vector3D(1, -1, -1), Vector3D(1, -1, 1),
		Vector3D(1, -1, 1), Vector3D(-1, -1, 1), Vector3D(-1, -1, -1),
		Vector3D(1, -1, -1), Vector3D(-1, -1, -1), Vector3D(-1, 1, -1),
		Vector3D(-1, 1, -1), Vector3D(1, 1, -1), Vector3D(1, -1, -1)
	};

}