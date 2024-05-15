#include <Windows.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"


#include "Polygon3D.h"
#include <iostream>
#include <fstream>

/// <summary>
/// Constructor using a custom vector scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Polygon3D::Polygon3D(Vector3D scale, float newTranslationSpeed, float newRotationSpeed, std::string choosenTexture)
{
	//SetUpVertices();
	translationSpeed = newTranslationSpeed;
	rotationSpeed = newRotationSpeed;

	material = new Material();
	/*LoadVerticesFromFile();
	LoadTextureFromFile();*/
}

/// <summary>
/// Constructor using a uniform float scale
/// </summary>
/// <param name="scale">Scale of the Cube</param>
/// <param name="newTranslationSpeed">Speed of axis translation</param>
/// <param name="newRotationSpeed">Speed of object rotation</param>
Polygon3D::Polygon3D(float scale, float newTranslationSpeed, float newRotationSpeed, std::string choosenTexture)
{
	//SetUpVertices();
	translationSpeed = newTranslationSpeed;
	rotationSpeed = newRotationSpeed;

	material = new Material();
	/*LoadVerticesFromFile();
	LoadTextureFromFile();*/
}

/// <summary>
/// Draws the polygon with random rotation and translation movement
/// </summary>
void Polygon3D::Draw()
{
	textCoordIterator = 0;//resets texcoord iterator each draw call
	glBindTexture(GL_TEXTURE_2D, this->texture->GetID());
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
		////Iterates through colours to ensure each triangle is coloured differently
		//if (i % 3 == 0)
		//{
		//	SetColor((Color)colorIterator);

		//	glColor4f(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);

		//	colorIterator++;

		//	//prevents triangle from being black to ensure it can be seen
		//	if (colorIterator == BLACK)
		//	{
		//		colorIterator++;
		//	}

		//	//loops back to RED
		//	if (colorIterator == END_OF_COLOR_ENUM)
		//	{
		//		colorIterator = 0;
		//	}
		//}



		//glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z); //draws vertex
		
		if (normalsIterator <= indexedNormals.size() - 1)
		{
			glNormal3f(indexedNormals[normalsIterator].x, indexedNormals[normalsIterator].y, indexedNormals[normalsIterator].z);
		}
		else
		{
			normalsIterator = 0; //loops texCoord iterator to ensure all surfaces are covered
		}

		normalsIterator++;
		

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
		if (textCoordIterator <= indexedTextCoords.size() - 1)
		{
			glTexCoord2f(indexedTextCoords[textCoordIterator].u, indexedTextCoords[textCoordIterator].v);
		}
		else
		{
			textCoordIterator = 0; //loops texCoord iterator to ensure all surfaces are covered
		}
		
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);

		textCoordIterator++;
	}

	glEnd();
	glPopMatrix();



}

/// <summary>
/// Reads vertices from a txt file to store in the object's vertex list
/// </summary>
/// <returns></returns>
bool Polygon3D::LoadVerticesFromFile()
{
	std::string filePath = "Polygons/" + meshTextFileName + ".txt";

	std::ifstream inFile;

	inFile.open(filePath);

	if (!inFile.good())
	{
		std::cerr << "Can't open txt file:  " << filePath << std::endl;
		return false;
	}

	int x, y, z;
	char c;

	int numVertices, numNormals, numTextCoords, numIndices;

	inFile >> numVertices;
	//indexedVertices = new Vector3D[numVertices];

	for (int i = 0; i < numVertices; i++)
	{
		inFile >> x >> y >> z;
		indexedVertices.push_back(Vector3D(x, y, z));
	}

	inFile >> numTextCoords;
	//indexedNormals = new Vector3D[numNormals];

	for (int i = 0; i < numTextCoords; i++)
	{
		inFile >> x >> y;
		indexedTextCoords.push_back(TexCoord(GLfloat(x), GLfloat(y)));
	}

	inFile >> numNormals;
	//indexedNormals = new Vector3D[numNormals];

	for (int i = 0; i < numNormals; i++)
	{
		inFile >> x >> y >> z;
		indexedNormals.push_back(Vector3D(x, y, z));
	}


	inFile >> numIndices;
	indiciesAmount = numIndices;
	//indices = new int[numIndices];

	for (int i = 0; i < numIndices; i++)
	{
		inFile >> x;
		indices.push_back(x);
	}

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

/// <summary>
/// Reads vertices from a txt file to store in the object's vertex list
/// </summary>
/// <returns></returns>
bool Polygon3D::LoadOBJFromFile()
{
	std::string filePath = "Polygons/" + meshTextFileName + ".obj";

	std::ifstream inFile;

	inFile.open(filePath);

	if (!inFile.good())
	{
		std::cerr << "Can't open obj tfile:  " << filePath << std::endl;
		return false;
	}

	int x, y, z;
	char c;

	int numVertices, numNormals, numIndices;

	inFile >> numVertices;
	//indexedVertices = new Vector3D[numVertices];


	for (int i = 0; i < numVertices; i++)
	{
		inFile >> x >> y >> z;
		indexedVertices.push_back(Vector3D(x, y, z));
	}

	inFile >> numNormals;
	//indexedNormals = new Vector3D[numNormals];

	for (int i = 0; i < numNormals; i++)
	{
		inFile >> x >> y >> z;
		indexedNormals.push_back(Vector3D(x, y, z));
	}

	inFile >> numIndices;
	indiciesAmount = numIndices;
	//indices = new int[numIndices];

	for (int i = 0; i < numIndices; i++)
	{
		inFile >> x;
		indices.push_back(x);
	}

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

bool Polygon3D::LoadTextureFromFile()
{
	//loads in a new texture
	//Texture2D* texture = new Texture2D();
	texture = new Texture2D();
	bool success = texture->LoadTexture("Textures/" + textureFileName + ".raw", 512, 512);
	//glBindTexture(GL_TEXTURE_2D, texture->GetID()); //binds the new texture

	return success;
}



///// <summary>
///// Returns an array of color values
///// </summary>
///// <param name="color">The color being requested</param>
///// <param name="colorArray">Array of float values representing R, G, B and A</param>
//void Polygon3D::SetColor(const Color color)
//{
//	this->color = color;
//	switch (color)
//	{
//	case RED:
//		colorArray[0] = 1.0f;
//		colorArray[1] = 0.0f;
//		colorArray[2] = 0.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case ORANGE:
//		colorArray[0] = 1.0f;
//		colorArray[1] = 0.5f;
//		colorArray[2] = 0.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case YELLOW:
//		colorArray[0] = 1.0f;
//		colorArray[1] = 1.0f;
//		colorArray[2] = 0.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case GREEN:
//		colorArray[0] = 0.0f;
//		colorArray[1] = 1.0f;
//		colorArray[2] = 0.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case LIGHTBLUE:
//		colorArray[0] = 0.0f;
//		colorArray[1] = 1.0f;
//		colorArray[2] = 1.0f;
//		colorArray[3] = 1.0f;
//		break;
//
//	case DARKBLUE:
//		colorArray[0] = 0.0f;
//		colorArray[1] = 0.0f;
//		colorArray[2] = 1.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case PURPLE:
//		colorArray[0] = 1.0f;
//		colorArray[1] = 0.0f;
//		colorArray[2] = 1.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case BLACK:
//		colorArray[0] = 0.0f;
//		colorArray[1] = 0.0f;
//		colorArray[2] = 0.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	case WHITE:
//		colorArray[0] = 1.0f;
//		colorArray[1] = 1.0f;
//		colorArray[2] = 1.0f;
//		colorArray[3] = 0.0f;
//		break;
//
//	default: //returns white if current color is not supported
//		colorArray[0] = 1.0f;
//		colorArray[1] = 1.0f;
//		colorArray[2] = 1.0f;
//		colorArray[3] = 0.0f;
//		break;
//	}
//}

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

/// <summary>
/// Moves the polygon along a given axis
/// </summary>
/// <param name="translationVector">The direction of translation</param>
void Polygon3D::TranslatePolygon(Vector3D translationVector)
{
	glTranslatef(translationVector.x, translationVector.y, translationVector.z);

	if (translation > 0.5f && !switchDirection)
	{
		switchDirection = true;
		chosenTranslationAxis = rand() % 10;
	}
	else if (translation < -0.5f && switchDirection)
	{
		switchDirection = false;
		chosenTranslationAxis = rand() % 10;
	}
	
}

/// <summary>
/// Rotates the polygon in a given direction
/// </summary>
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

void Polygon3D::ToggleTranformation(ToggleStates transformationToToggle)
{
	switch (transformationToToggle)
	{
	case TRANSLATION:
		m_customisationToggles.m_translatePolygon = !m_customisationToggles.m_translatePolygon;
		break;

	case ROTATION:
		m_customisationToggles.m_rotatePolygon = !m_customisationToggles.m_rotatePolygon;
		break;

	case SCALE:
		m_customisationToggles.m_scalePolygon = !m_customisationToggles.m_scalePolygon;
		break;

	case VISIBILITY:
		m_customisationToggles.isVisible = !m_customisationToggles.isVisible;
		break;
	}
}

bool Polygon3D::GetToggleStatus(ToggleStates toggleRequest)
{
	switch (toggleRequest)
	{
	case Polygon3D::TRANSLATION:
		return m_customisationToggles.m_translatePolygon;

	case Polygon3D::ROTATION:
		return m_customisationToggles.m_rotatePolygon;

	case Polygon3D::SCALE:
		return m_customisationToggles.m_scalePolygon;

	case Polygon3D::MATERIAL:
		break;

	case Polygon3D::LIGHTING:
		break;

	case Polygon3D::VISIBILITY:
		return m_customisationToggles.isVisible;

	default:
		break;
	}

	return true;
}