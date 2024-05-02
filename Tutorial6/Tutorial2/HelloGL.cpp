#include "HelloGL.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Header.h"
//#include "Teapot.h"
#include "Polygon3D.h"
#include <algorithm>
#include <time.h>


HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(0));
	
	InitGL(argc, argv);

	InitObjects();

	InitMenu();
	

	glutMainLoop();


}

HelloGL::~HelloGL(void)
{
	delete camera;
}

/// <summary>
/// Setup Objects
/// </summary>
void HelloGL::InitObjects()
{


	camera = new Camera();
	lighting = new Lighting();

	camera->eye.z = 1.0f;
	camera->up.y = 1.0f;

	lighting->ambient = { 1.2f, 1.2f, 1.2f, 1.0f };
	lighting->diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	lighting->specular = { 0.2f, 0.2f, 0.2f, 1.0f };
	lighting->position = { 0.0f, 0.0f, 0.0f, 1.0f };

	float newTranslation = 0;
	float newScale = 0;
	float newRotation = 0;

	Meshes newMesh = CUBE;
	Textures newTexture = PENGUINS;

	

	for (int i = 0; i < 20; i++)
	{
		newTranslation = rand() % 10; //random number between 0.001 and 0.1
		newTranslation /= 1000;

		newScale = rand() % 5; //random number between 0.001 and 0.1
		newScale /= 100;

		newRotation = rand() % 10; //random number between 0.001 and 0.1

		newMesh = Meshes(rand() % END_OF_MESH_ENUM); //chooses a random mesh to load
		newTexture = Textures(rand() % END_OF_TEXTURE_ENUM); //chooses a random mesh to load
		
		Transformation newMeshTransform;
		newMeshTransform.translation = newTranslation;
		newMeshTransform.rotation = newRotation;
		newMeshTransform.scale = newScale;

		SanitiseTransformation(newMeshTransform);

		switch (newMesh)
		{
		case HelloGL::CUBE:
			polygonList.push_back(new Cube(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, textureEnumToString[newTexture]));
			break;
		case HelloGL::PYRAMID:
			polygonList.push_back(new Pyramid(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, textureEnumToString[newTexture]));
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// Set up OpenGL
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this); //sets the current gl instance pointer to this current instance
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); //enables double buffering
	glutInitWindowSize(800, 800); // creates a 800x800 window
	glutInitWindowPosition(100, 100); //alters the window - to - shape - drawing ratio
	glutCreateWindow("Simple OpenGL Program"); //window title
	glutDisplayFunc(GLUTCallbacks::Display); //draws window
	glutTimerFunc(refreshRate, GLUTCallbacks::GameTimer, refreshRate);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);


	glMatrixMode(GL_PROJECTION); //switches transformation pipeline to 3D matrix
	glLoadIdentity(); //loads the identity matrix (sets matrix back to 1)

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); //sets viewport to be entire window

	//sets correct scene perspective
	//field of view, aspect ratio, near clipping distance, far clipping distance
	gluPerspective(45, 1, 0, 1000);

	
	glMatrixMode(GL_MODELVIEW); //switches pipeline to model view to work with models

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Backwards culling
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);*/
	

	//SetLight(&lighting);

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::InitMenu()
{
	menuIDs[TRANSLATION_STATUS_MENU] = glutCreateMenu(GLUTCallbacks::TranslationsMenu);

	std::string polygonStatus = "";
	for (int i = 0; i < polygonList.size(); i++)
	{
		glutAddMenuEntry(CreateTranformationMenuText(i, polygonList[i]->GetTranslationStatus()).c_str(), i);
	}

	menuIDs[TRANSFORMATION_MENU] = glutCreateMenu(GLUTCallbacks::TransformationsMenu);

	/*glutAddMenuEntry("Toggle Auto Translation", 0);
	glutAddMenuEntry("Toggle Auto Rotation", 1);
	glutAddMenuEntry("Toggle Auto Scale", 2);*/

	glutAddSubMenu("Toggle Auto Translation", menuIDs[TRANSLATION_STATUS_MENU]);

	

	menuIDs[TOGGLE_MENU] = glutCreateMenu(GLUTCallbacks::ToggleMenu);

	glutAddSubMenu("Toggle Auto Transformations", menuIDs[TRANSFORMATION_MENU]);


	menuIDs[POLYGON_MENU] = glutCreateMenu(GLUTCallbacks::PolygonMenu);

	//adds all loaded polygons to the polygon menu
	std::string polygonName = "";
	for (int i = 0; i < polygonList.size(); i++)
	{
		polygonName = "Shape " + std::to_string(i) + ": " + polygonList[i]->GetPolygonName();
		glutAddMenuEntry(polygonName.c_str(), i);
	}

	//glutSetMenu(0);
	glutAddSubMenu("Toggle Settings", menuIDs[TOGGLE_MENU]);

	glutAddMenuEntry("None", -1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}



void HelloGL::PolygonMenu(int chosenOption)
{
	if (chosenOption > -1 && chosenOption < polygonList.size())
	{
		printf("%s %i is chosen", polygonList[chosenOption]->GetPolygonName().c_str(), chosenOption);
	}
}

void HelloGL::ToggleMenu(int chosenOption)
{
	printf("Chosen Toggle option: %i", chosenOption);
}

void HelloGL::TransformationsMenu(int chosenOption)
{
	printf("Chosen Transformation option: %i", chosenOption);
}

void HelloGL::TranslationsMenu(int chosenOption)
{
	printf("Chosen Translation option: %i", chosenOption);
	polygonList[chosenOption]->ToggleTranslation(Polygon3D::TRANSLATION);

	std::string newTranslationStatus = CreateTranformationMenuText(chosenOption, polygonList[chosenOption]->GetTranslationStatus());

	//glutChangeToMenuEntry(menuIDs[TRANSLATION_STATUS_MENU], newTranslationStatus.c_str(), chosenOption);
	
}

std::string HelloGL::CreateTranformationMenuText( const int polygonID, const bool isActive)
{
	std::string polygonStatus = "";

	switch (isActive)
	{
	case true:
		polygonStatus = "Shape " + std::to_string(polygonID) + ": ON";
		break;

	case false:
		polygonStatus = "Shape " + std::to_string(polygonID) + ": OFF";
		break;
	}

	return polygonStatus;
}

Transformation HelloGL::SanitiseTransformation(Transformation newMeshTransform)
{
	//Creates a cube with randomised properties
	if (newMeshTransform.translation == 0.000f)
	{
		newMeshTransform.translation = 0.0001f;
		//polygonList.push_back(new Pyramid(newMeshTransform.scale, 0.0001f, newMeshTransform.rotation)); //creates a new cube object
	}
	else if (newMeshTransform.scale == 0.00f)
	{
		newMeshTransform.scale = 0.01f;
		//polygonList.push_back(new Pyramid(0.01f, newMeshTransform.translation, newMeshTransform.rotation)); //creates a new cube object
	}
	else if (newMeshTransform.rotation == 0.0f)
	{
		newMeshTransform.rotation = 1.0f;
		//polygonList.push_back(new Pyramid(newMeshTransform.scale, newMeshTransform.translation, 1.0f)); //creates a new cube object
	}

	return newMeshTransform;

}

void HelloGL::DrawTextString(std::string text, Vector3D position, Vector3D color)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRasterPos2f(0.0f, 0.0f);
	glColor3f(color.x, color.y, color.z);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str());
	glPopMatrix();
}

/// <summary>
/// Draws objects into the scene
/// </summary>
void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	/*float triangleCoordinates[3][2];

	vertex1 = std::make_tuple(-0.75f, 0.6f);
	vertex2 = std::make_tuple(-0.55f, 0.6f);
	vertex3 = std::make_tuple(-0.55f, 0.4f);
	vertex4 = std::make_tuple(-0.75f, 0.4f);*/

	//glPushMatrix();

	for (int i = 0; i < polygonList.size(); i++)
	{
		polygonList[i]->Draw();
	}
	
	DrawTextString("TEST STRING", { -1.4f, 0.7f, -1.0f }, { 0.0f, 1.0f, 0.0f });

	glFlush(); //flushes scene drawn to graphics card (draws polygon on the screen)
	glutSwapBuffers();
}

/// <summary>
/// Main Game Loop
/// </summary>
void HelloGL::Update() 
{
	glLoadIdentity(); //resets pre-existing matrix transformations

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(lighting->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lighting->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(lighting->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(lighting->position.x));
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z); //moves the camera

	glutPostRedisplay(); //forces the scene to redraw itself
	
	//triangleRotation = UpdateRotation(triangleRotation, 2.0f);

	Vector3D polygonRotation = Vector3D();

}


/// <summary>
/// Enables keyboard input for camera controls
/// </summary>
/// <param name="key">key being pressed</param>
/// <param name="x">x co-ordinate</param>
/// <param name="y">y co-ordinate</param>
void HelloGL::Keyboard(unsigned char key, int x, int y)
{    
	switch (key)
	{
	case 'k':
		camera->eye.x -= 1.00f;
		break;

	case ';':
		camera->eye.x += 1.0f;
		break;

	case 'o':
		camera->eye.y += 2.0f;
		break;

	case 'l':
		camera->eye.y -= 2.0f;
		break;

	case 'i':
		camera->eye.z -= 3.0f;
		break;

	case 'p':
		camera->eye.z += 3.0f;
		break;

	case 'a':
		std::get<0>(translationAxis) += -0.02f;
		break;

	case 'd':
		std::get<0>(translationAxis) += 0.02f;
		break;

	case 'w':
		std::get<1>(translationAxis) += 0.02f;
		break;

	case 's':
		std::get<1>(translationAxis) += -0.02f;
		break;

	case 'q':
		std::get<2>(translationAxis) += -0.2f;
		break;

	case 'e':
		std::get<2>(translationAxis) += 0.2f;
		break;

	case '1':
		rotationAxis = std::make_tuple(-1.0f, 0.0f, 0.0f);
		polygonRotation = UpdateRotation(polygonRotation, -2.0f);
		break;

	case '4':
		rotationAxis = std::make_tuple(0.0f, 0.0f, -1.0f);
		polygonRotation = UpdateRotation(polygonRotation, -2.0f);
		break;

	case '6':
		rotationAxis = std::make_tuple(0.0f, 0.0f, -1.0f);
		polygonRotation = UpdateRotation(polygonRotation, 2.0f);
		break;

	
	}

	/*if (key == 'd') 
	{
		polygonRotation = UpdateRotation(polygonRotation, 2.0f);
	}
	else if (key == 'a')
	{
		polygonRotation = UpdateRotation(polygonRotation, -2.0f);
	}*/
	
}


float HelloGL::UpdateRotation(float rotation, float rotationSpeed)
{
	rotation += rotationSpeed;

	if (rotation >= 360.0f)
	{
		rotation = 0.1f + (360.0f - rotation);
	}
	else if (rotation <= 0.0f)
	{
		rotation = 359.9f + rotation;
	}

	return rotation;

}

//Vector3D HelloGL::UpdateRotation(Vector3D rotation, Vector3D rotationSpeed)
//{
//	//rotation = rotation + rotationSpeed;
//
//	//if (rotation >= 360.0f)
//	//{
//	//	rotation = 0.1f + (360.0f - rotation);
//	//}
//	//else if (rotation <= 0.0f)
//	//{
//	//	rotation =  rotation + 359.9f;
//	//}
//
//	return rotation;
//
//}

#pragma region Draw2D Functions (UNUSED)

/// <summary>
/// Draws a preset rectangle
/// </summary>
/// <param name="r">red value</param>
/// <param name="g">blue value</param>
/// <param name="b">green value</param>
/// <param name="a">alpha value</param>
void HelloGL::DrawQuadrilateral(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3, const std::tuple<float, float>& vertex4)
{
	glPushMatrix();
	//glTranslatef(std::get<0>(translationAxis), std::get<1>(translationAxis), std::get<2>(translationAxis));
	//begins matrix calculation
	//glTranslatef(0, 0, 0);

	//glRotatef(polygonRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of quadet
		glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2)); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex3), std::get<1>(vertex3)); //defines 3rd point of triangle
		glVertex2f(std::get<0>(vertex4), std::get<1>(vertex4)); //defines 3rd point of triangle
		glEnd(); //stops drawing polygon (stops listening for instructions
	}
	
	glPopMatrix();
}

/// <summary>
/// Draws a triangle of any size/angle relationship
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
void HelloGL::DrawFreeTriangle(std::array<float, 4>& colorCode, const std::tuple<float,float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3)
{
	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2)); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex3), std::get<1>(vertex3)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

}


/// <summary>
/// Draws an equilateral triangle
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1">Starting position of the triangle</param>
/// <param name="sideLength">Length of all sides</param>
void HelloGL::DrawEqualTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength)
{
	float heightX = std::get<0>(vertex1) + (sideLength / 2); //position's height point halfway between side length
	float heightY= std::get<1>(vertex1) + (sideLength * (sqrt(3) / 2)); //calulates height point's y position (triangle height)
	
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//begins matrix calculation
	//glTranslatef(0, 0, 0);
	/*float localRotation = polygonRotation;
	localRotation += polygonRotationSpeed * 2.0f;

	if (localRotation >= 360.0f)
	{
		localRotation = polygonRotationSpeed * 2.0f;
	}*/

	float localRotation = triangleRotation;
	localRotation += polygonRotationSpeed * 2.0f;

	if (localRotation >= 360.0f)
	{
		localRotation = polygonRotationSpeed * 2.0f;
	}


	glRotatef(triangleRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(heightX, heightY); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex1) + sideLength, std::get<1>(vertex1)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

	glPopMatrix();

}


/// <summary>
/// Draws a right angle triangle
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1"></param>
/// <param name="sideLength"></param>
void HelloGL::DrawRightTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength)
{

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1) + sideLength); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex1) + sideLength, std::get<1>(vertex1)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

}

/// <summary>
/// Draws and isoceles triangle
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1">Starting position of the triangle</param>
/// <param name="sideLength">Length of side</param>
/// <param name="bottomLength">Length of bottom</param>
void HelloGL::DrawIsoTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength, const float bottomLength)
{
	float heightX = std::get<0>(vertex1) + (bottomLength / 2); //position's height point halfway between side length
	float heightY = std::get<1>(vertex1) + sqrtf((sideLength * sideLength - ((bottomLength * bottomLength) / 4))); //calulates height point's y position (triangle height)

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(heightX, heightY); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex1) + bottomLength, std::get<1>(vertex1)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

	

}


/// <summary>
/// Draws a polygon with equal sides and angles
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1">Starting position of the triangle</param>
/// <param name="numberOfSides">Number of sides in polygon</param>
/// <param name="sideLength">Length of side</param>
void HelloGL::DrawEqualPolygon(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const int numberOfSides, const float sideLength, const std::tuple<float, float, float>& rotationAxis, const float rotationSpeed)
{
	float pointX = 0.0f;
	float pointY = 0.0f;

	float polygonAngle = 360.0f / numberOfSides; //determines the internal angles of the sides

	
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//RotatePolygon(rotationAxis, rotationSpeed);

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		for (int i = 0; i < numberOfSides; i++)
		{
			//Determines co-ordinates for next point
			pointX = sideLength * cos(2 * 3.14f * i / numberOfSides);
			pointY = sideLength * sin(2 * 3.14f * i / numberOfSides);

			//Uses the previous point as an offset to draw the next part of the polygon
			glVertex2f(std::get<0>(vertex1) + pointX, std::get<1>(vertex1) + pointY);
		}

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

	//glTranslatef(std::get<0>(vertex1), std::get<1>(vertex1), 0.0f);
	glPopMatrix(); //begins matrix calculation

}

void HelloGL::Draw3D()
{
	glPushMatrix();
	glTranslatef(std::get<0>(translationAxis), std::get<1>(translationAxis), std::get<2>(translationAxis));
	//begins matrix calculation
	//glTranslatef(0, 0, 0);

	glRotatef(polygonRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon

	//glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color
	glutWireTeapot(0.1);

	glPopMatrix();
}

//void HelloGL::RotatePolygon(const std::tuple<float, float, float>& rotationAxis, const float rotationSpeed)
//{
//	 //begins matrix calculation
//	//glTranslatef(0, 0, 0);
//	polygonRotation += polygonRotationSpeed * rotationSpeed;
//
//	if (polygonRotation >= 360.0f)
//	{
//		polygonRotation = 0.0f;
//	}
//
//	glRotatef(polygonRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon
//}

#pragma endregion


/// <summary>
/// Returns the vector index of the provided polygon
/// </summary>
/// <param name="polygon">The polygon to find</param>
/// <returns>The index of the polygon (returns -1 if not found)</returns>
int HelloGL::FindPolygonInList(Polygon3D* polygon)
{
	int indexLocation = -1;

	for (int i = 0; i < polygonList.size(); i++)
	{
		//if (polygonList[i].get() == polygon)
		if (polygonList[i] == polygon)
		{
			indexLocation = i;
		}
	}

	return indexLocation;
}


/// <summary>
/// Deletes the given polygon from the system
/// </summary>
/// <param name="polygon">The polygon to be deleted</param>
void HelloGL::DeletePolygon(Polygon3D* polygon)
{
	int oldLocation = FindPolygonInList(polygon);

	delete polygon;
	polygon = nullptr;

	polygonList.erase(polygonList.begin() + oldLocation); //removes the deleted polygon from the vector list
	
}

//void HelloGL::SetLight(Lighting* light, int ID)
//{
//	switch (ID)
//	{
//	case 0:
//		glLightfv(GL_LIGHT0, GL_AMBIENT, light->red);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, light->green);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, light->blue);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, light->position);
//
//	default:
//	}
//	
//}