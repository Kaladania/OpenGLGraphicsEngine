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
	//renders material properties
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
	else if (m_customisationToggles.manualControl) //if automatic control is disabled, manual control is enabled by default
	{
		TranslatePolygon(position); //sets translation to update based on objects position for manual control
		translation = position; //updates the translation starting point
		chosenTranslationAxis = 6; //ensures that full translation is passed on continuation of auto-movement for seemless transition
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


	glBegin(GL_TRIANGLES);

	//loops through vertex list and draws the polygon face according to the layout specified by the indicies
	//as no normals or text co-ords are specified, only the vertices are drawn
	for (int i = 0; i < indiciesAmount; i++)
	{
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
	}

	glEnd();
	glPopMatrix();

}



/// <summary>
/// Reads vertices from an obj file to store in the object's vertex and indicies list
/// </summary>
/// <returns>if the load was succecssful</returns>
bool Teapot::LoadOBJFromFile()
{
	//opens the file corrisponding to the corret mesh title
	std::string filePath = "Polygons/" + meshTextFileName + ".obj";

	std::ifstream inFile;

	inFile.open(filePath);

	//returns an error if the file is unable to be opened
	if (!inFile.good())
	{
		std::cerr << "Can't open obj tfile:  " << filePath << std::endl;
		return false;
	}

	char identifier; //holds the current identifier of the line in the obj

	inFile >> identifier;

	std::string float1, float2, float3; //holds the vertices found in the current line 

	//loops continously through the file
	while (inFile.peek() != EOF)
	{
		//stores the 3 floats as strings so that their signs stay intact
		inFile >> float1;
		inFile >> float2;
		inFile >> float3;
		
		//converts the strings to floats before adding them to the indexed Vertcies
		indexedVertices.push_back(Vector3D(std::stof(float1), std::stof(float2), std::stof(float3)));

		//gets the next identifier
		inFile >> identifier;

		//breaks the moment the identifier switches from 'v' to 'f'
		if (identifier != 'v')
		{
			break;
		}
	}

	//runs for the remainder of the file
	while (inFile.peek() != EOF)
	{
		//explicitly stores the 3 float indices in the line in order to make it easier to access the next identifer
		inFile >> float1;
		inFile >> float2;
		inFile >> float3;

		//converts each string to a signed float and converts said float to a 0-indexed value before storing it as an index
		indices.push_back(std::stof(float1) - 1);
		indices.push_back(std::stof(float2) - 1);
		indices.push_back(std::stof(float3) - 1);

		inFile >> identifier;
	}

	//gets the total index amount from the vector size
	indiciesAmount = indices.size();

	inFile.close();

}