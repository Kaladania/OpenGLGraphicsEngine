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
Polygon3D::Polygon3D(Vector3D scale, float newTranslationSpeed, float newRotationSpeed, Textures chosenTexture)
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
Polygon3D::Polygon3D(float scale, float newTranslationSpeed, float newRotationSpeed, Textures chosenTexture)
{
	translationSpeed = newTranslationSpeed;
	rotationSpeed = newRotationSpeed;

	material = new Material();
}

/// <summary>
/// Draws the polygon with random rotation and translation movement
/// </summary>
void Polygon3D::Draw()
{
	textCoordIterator = 0;//resets texcoord iterator each draw call

	if (texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, this->texture->GetID());
	}

	//renders object material
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


	

	int colorIterator = 0;
	int normalsIterator = 0;
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < indiciesAmount; i++)
	{
		
		if (normalsIterator <= indexedNormals.size() - 1)
		{
			glNormal3f(indexedNormals[normalsIterator].x, indexedNormals[normalsIterator].y, indexedNormals[normalsIterator].z);
		}
		else
		{
			normalsIterator = 0; //loops texCoord iterator to ensure all surfaces are covered
		}

		normalsIterator++;
		
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

	//loads vertexs
	inFile >> numVertices;

	for (int i = 0; i < numVertices; i++)
	{
		inFile >> x >> y >> z;
		indexedVertices.push_back(Vector3D(x, y, z));
	}

	inFile >> numTextCoords;

	for (int i = 0; i < numTextCoords; i++)
	{
		inFile >> x >> y;
		indexedTextCoords.push_back(TexCoord(GLfloat(x), GLfloat(y)));
	}

	//loads normals
	inFile >> numNormals;

	for (int i = 0; i < numNormals; i++)
	{
		inFile >> x >> y >> z;
		indexedNormals.push_back(Vector3D(x, y, z));
	}


	//loads indices
	inFile >> numIndices;
	indiciesAmount = numIndices;

	for (int i = 0; i < numIndices; i++)
	{
		inFile >> x;
		indices.push_back(x);
	}

	inFile.close();

}


bool Polygon3D::LoadTextureFromFile(Textures newTexture)
{
	//loads in a new texture

	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}

	texture = new Texture2D();
	std::string filePath = "";
	int tileSize = 0;

	switch (newTexture)
	{
	case Polygon3D::PENGUINS:

		filePath = "Textures/Penguins.raw";
		tileSize = 512;
		break;

	case Polygon3D::STARS:

		filePath = "Textures/Stars.raw";
		tileSize = 512;
		break;

	case Polygon3D::END_OF_TEXTURE_ENUM:
		break;
	default:
		break;
	}

	bool success = texture->LoadTexture(filePath, tileSize, tileSize);

	return success;
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
	}
}

/// <summary>
/// Moves the polygon along a given axis
/// </summary>
/// <param name="translationVector">The direction of translation</param>
void Polygon3D::TranslatePolygon(Vector3D translationVector)
{
	glTranslatef(translationVector.x, translationVector.y, translationVector.z);

	position = translationVector;

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

	case MANUAL:
		m_customisationToggles.manualControl = !m_customisationToggles.manualControl;
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