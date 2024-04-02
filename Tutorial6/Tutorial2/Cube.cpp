#include "Cube.h"
#include <iostream>


Cube::Cube(Vector3D scale, Vector3D rotationSpeed) : Polygon3D(scale, rotationSpeed)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	this->rotationSpeed = rotationSpeed;

	ScalePolygon(scale, vertexList);

}

Cube::Cube(float scale, Vector3D rotationSpeed) : Polygon3D(scale, rotationSpeed)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	this->rotationSpeed = rotationSpeed;

	ScalePolygon(scale, vertexList);
}

void Cube::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	//glRotatef(10.0f, rotation.x, rotation.y, rotation.z); //rotates the drawn polygon

	//polygonRotation = polygonList[i]->GetRotation();
	printf("%f, %f, %f \n", rotation.x, rotation.y, rotation.z);

	//rotation = rotation + 0.1f;

	//glRotatef(rotationSpeed.z, 0.0f, 0.0f, 0.0f); //rotates the drawn polygon

	if (switchDirection)
	{
		TranslatePolygon(Vector3D(0.0f, 0.0f, -0.1f));
	}
	else 
	{
		TranslatePolygon(Vector3D(0.0f, 0.0f, 0.1f));
	}
	


	int colorIterator = 0;
	glBegin(GL_TRIANGLES);

	/*SetColor(RED);

	glColor4f(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);*/

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
	glFlush();
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