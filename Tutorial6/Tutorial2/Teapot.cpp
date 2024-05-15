#include "Teapot.h"


#include <iostream>
#include <fstream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Teapot::Teapot(Vector3D scale, float newTranslationSpeed, float newRotationSpeed, Textures chosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, chosenTexture)
{

	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon
	translationSpeed = newTranslationSpeed;

	meshTextFileName = "Teapot";
	//textureFileName = "Penguin";

	material->ambient = { 1.0f, 0.5f, 0.2f, 1.0f };
	material->diffuse = { 1.80f, 1.05f, 1.05f, 1.0f };
	material->specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material->shininess = 20.0f;

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
Teapot::Teapot(float scale, float newTranslationSpeed, float newRotationSpeed, Textures chosenTexture) : Polygon3D(scale, newTranslationSpeed, newRotationSpeed, chosenTexture)
{
	sides = 8; //number of sides in cube
	vertexAmount = 8; //number of vertices in polygon

	meshTextFileName = "Teapot";
	//textureFileName = "Penguin";

	material->ambient = { 1.0f, 0.5f, 0.2f, 1.0f };
	material->diffuse = { 1.80f, 1.05f, 1.05f, 1.0f };
	material->specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material->shininess = 20.0f;

	LoadOBJFromFile();

	ScalePolygon(scale, indexedVertices);
}

Teapot::~Teapot()
{

}

/// <summary>
/// Draws the polygon with random rotation and translation movement
/// </summary>
void Teapot::Draw()
{
	textCoordIterator = 0;//resets texcoord iterator each draw call

	if (texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, this->texture->GetID());
	}
	/*glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, TexCoord);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);*/

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(material->specular.x));

	glPushMatrix();

	//Inverts the rotation and translation
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

	if (m_customisationToggles.m_translatePolygon)
	{
		//Applys a random translation direction
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

		case(7):
			TranslatePolygon(Vector3D(-(translation.x), 0.0f, 0.0f));
			break;

		case(8):
			TranslatePolygon(Vector3D(-(translation.x), translation.y, 0.0f));
			break;

		case(9):
			TranslatePolygon(Vector3D(-(translation.x), 0.0f, translation.z));
			break;

		case(10):
			TranslatePolygon(Vector3D(-(translation.x), translation.y, translation.z));
			break;
		}
	}


	if (m_customisationToggles.m_rotatePolygon)
	{
		//Applies a random rotation direction
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
	}




	int colorIterator = 0;
	int normalsIterator = 0;
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < indiciesAmount; i++)
	{

		//glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z); //draws vertex

		//if (normalsIterator <= indexedNormals.size() - 1)
		//{
		//	glNormal3f(indexedNormals[normalsIterator].x, indexedNormals[normalsIterator].y, indexedNormals[normalsIterator].z);
		//}
		//else
		//{
		//	normalsIterator = 0; //loops texCoord iterator to ensure all surfaces are covered
		//}

		//normalsIterator++;


		//switch (i)
		//{
		//case 0:
		//	glTexCoord2f(0.0f, 0.0f);

		//case 1:
		//	glTexCoord2f(0.0f, 1.0f);

		//case 2:
		//	glTexCoord2f(1.0f, 1.0f);
		//}
		//glTexCoord2f(textureCoordinates[i].u, textureCoordinates[i].v);
		//glTexCoord2f(0.0f, 0.0f);
		//if (textCoordIterator <= indexedTextCoords.size() - 1)
		//{
		//	glTexCoord2f(indexedTextCoords[textCoordIterator].u, indexedTextCoords[textCoordIterator].v);
		//}
		//else
		//{
		//	textCoordIterator = 0; //loops texCoord iterator to ensure all surfaces are covered
		//}

		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);

		//textCoordIterator++;
	}

	glEnd();
	glPopMatrix();



}



/// <summary>
/// Reads vertices from a txt file to store in the object's vertex list
/// </summary>
/// <returns></returns>
bool Teapot::LoadOBJFromFile()
{
	std::string filePath = "Polygons/" + meshTextFileName + ".obj";

	std::ifstream inFile;

	inFile.open(filePath);

	if (!inFile.good())
	{
		std::cerr << "Can't open obj tfile:  " << filePath << std::endl;
		return false;
	}

	float x, y, z;
	char c;

	char identifier, signX, signY, signZ;
	int numVertices, numNormals, numIndices;

	inFile >> identifier;

	std::string float1, float2, float3;
	Vector3D tempVector;
	//indexedVertices = new Vector3D[numVertices];

	while (true)
	{
		inFile >> float1;
		inFile >> float2;
		inFile >> float3;
		//float test = std::stof(line);
		//printf("%f\n\n%f", test, std::stof(line));
		indexedVertices.push_back(Vector3D(std::stof(float1), std::stof(float2), std::stof(float3)));

		inFile >> identifier;

		if (identifier != 'v')
		{
			break;
		}
	}

	while (inFile.peek() != EOF)
	{
		inFile >> float1;
		inFile >> float2;
		inFile >> float3;
		//float test = std::stof(line);
		//printf("%f\n\n%f", test, std::stof(line));
		indices.push_back(std::stof(float1) - 1);
		indices.push_back(std::stof(float2) - 1);
		indices.push_back(std::stof(float3) - 1);

		inFile >> identifier;
	}

	indiciesAmount = indices.size();

	/*for (int i = 1; i < numVertices; i++)
	{
		inFile >> w >> x >> y >> z;
		indexedVertices.push_back(Vector3D(x, y, z));
	}*/

	//inFile >> numNormals;
	//indexedNormals = new Vector3D[numNormals];

	/*for (int i = 1; i < numNormals; i++)
	{
		inFile >> x >> y >> z;
		indexedNormals.push_back(Vector3D(x, y, z));
	}*/

	//inFile >> numIndices;
	//indiciesAmount = numIndices;
	////indices = new int[numIndices];

	//for (int i = 1; i < numIndices; i++)
	//{
	//	inFile >> x;
	//	indices.push_back(x);
	//}

	/*int numVertices, numNormals, numIndices;

	inFile >> numVertices;
	indexedVertices = new Vector3D[numVertices];

	for (int i = 0; i < numVertices; i++)
	{
		inFile >> x >> y >> z;
		indexedVertices[i] = Vector3D(x, y, z);
		printf("%i %i %i", x, y, z);
	}

	inFile >> numNormals;
	indexedNormals = new Vector3D[numNormals];

	for (int i = 0; i < numNormals; i++)
	{
		inFile >> x >> y >> z;
		indexedNormals[i] = Vector3D(x, y, z);
	}

	inFile >> numIndices;
	indices = new GLfloat[numIndices];

	for (int i = 0; i < numVertices; i++)
	{
		inFile >> x;
		indices[i] = x;
	}*/

	//while (!inFile.eof())
	//{
	//	while ((inFile >> x >> y >> z))
	//	{
	//		vertexList.push_back(Vector3D(x, y, z));
	//		//printf(" %i, %i, %i", x, y, z);
	//	}
	//}




	inFile.close();

}