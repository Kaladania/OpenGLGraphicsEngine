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
	camera = nullptr;

	delete lighting;
	lighting = nullptr;

	delete bottomText;
	bottomText = nullptr;
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

	

	for (int i = 0; i < 5; i++)
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
			//polygonList.push_back(new Cube(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, textureEnumToString[newTexture]));
			linkedPolygonList->MakeNode(&head, new Cube(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, textureEnumToString[newTexture]));
			break;
		case HelloGL::PYRAMID:
			//polygonList.push_back(new Pyramid(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, textureEnumToString[newTexture]));
			linkedPolygonList->MakeNode(&head, new Pyramid(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, textureEnumToString[newTexture]));
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < END_OF_MENU_ENUM; i++)
	{
		menusToUpdate[static_cast<Menus>(i)] = -1;
	}

	////sets all menu values to -1
	//for (auto& menu : menusToUpdate)
	//{
	//	menu.second = -1;
	//}

	newAnnouncement = "Number of Polygons Loaded: " + std::to_string(linkedPolygonList->Size());

	//linkedPolygonList->MakeNode(&head, polygonList[0]);
	//linkedPolygonList->PrintList(head);

	//head = linkedPolygonList->InsertFirst(&head, polygonList[1]);
	//linkedPolygonList->PrintList(head);

	//linkedPolygonList->InsertAfter(head, polygonList[3]);
	//linkedPolygonList->PrintList(head);

	///*linkedPolygonList->DeleteAfter(head->nextNode);
	//linkedPolygonList->PrintList(head);*/

	//linkedPolygonList->GetNode(head, 1);
	//linkedPolygonList->GetNode(head, 0);
	//linkedPolygonList->GetNode(head, 4);

	//linkedPolygonList->Find(head, polygonList[3]);
	//linkedPolygonList->Find(head, polygonList[4]);

	//linkedPolygonList->DeleteAt(head, 1);
	//linkedPolygonList->PrintList(head);

	//linkedPolygonList->DeleteList(&head);
	//linkedPolygonList->PrintList(head);
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

int test = 0;
void HelloGL::InitMenu()
{
	menuIDs[TRANSLATION_STATUS_MENU] = glutCreateMenu(GLUTCallbacks::TranslationsMenu);

	std::string polygonStatus = "";
	for (int i = 0; i < linkedPolygonList->Size(); i++)
	{
		glutAddMenuEntry(CreateTranformationMenuText(i, linkedPolygonList->GetNode(head, i)->data->GetTranslationStatus()).c_str(), i);

	}

	
	//glutAddSubMenu("Toggle Auto Translation 2", menuIDs[TRANSLATION_STATUS_MENU]);

	menuIDs[ROTATION_STATUS_MENU] = glutCreateMenu(GLUTCallbacks::RotationsMenu);

	//std::string polygonStatus = "";
	for (int i = 0; i < linkedPolygonList->Size(); i++)
	{
		glutAddMenuEntry(CreateTranformationMenuText(i, linkedPolygonList->GetNode(head, i)->data->GetTranslationStatus()).c_str(), i);

	}

	menuIDs[TRANSFORMATION_MENU] = glutCreateMenu(GLUTCallbacks::TransformationsMenu);
	
	glutAddSubMenu("Toggle Auto Translation", menuIDs[TRANSLATION_STATUS_MENU]);
	glutAddSubMenu("Toggle Auto Rotation", menuIDs[ROTATION_STATUS_MENU]);
	

	

	menuIDs[TOGGLE_MENU] = glutCreateMenu(GLUTCallbacks::ToggleMenu);

	glutAddSubMenu("Toggle Auto Transformations", menuIDs[TRANSFORMATION_MENU]);


	menuIDs[POLYGON_MENU] = glutCreateMenu(GLUTCallbacks::PolygonMenu);

	//adds all loaded polygons to the polygon menu
	std::string polygonName = "";
	for (int i = 0; i < linkedPolygonList->Size(); i++)
	{
		polygonName = "Shape " + std::to_string(i) + ": " + linkedPolygonList->GetNode(head, i)->data->GetPolygonName();
		glutAddMenuEntry(polygonName.c_str(), i);
	}

	//glutSetMenu(0);
	glutAddSubMenu("Toggle Settings", menuIDs[TOGGLE_MENU]);

	glutAddMenuEntry("None", -1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutMenuStatusFunc()//GLUT_MENU_NOT_IN_USE 

}



void HelloGL::PolygonMenu(int chosenOption)
{
	if (chosenOption > -1 && chosenOption < linkedPolygonList->Size())
	{
		printf("%s %i is chosen", linkedPolygonList->GetNode(head, chosenOption)->data->GetPolygonName().c_str(), chosenOption);
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

/// <summary>
/// Toggles the choosen polygon's state and sets a flag to update the menu entry
/// </summary>
/// <param name="chosenOption">Polygon to update</param>
void HelloGL::TranslationsMenu(int chosenOption)
{
	printf("Chosen Translation option: %i", chosenOption);
	linkedPolygonList->GetNode(head, chosenOption)->data->ToggleTranformation(Polygon3D::TRANSLATION);

	//changes the value of the menu update map to reflect that the choosen polygon needs its entry changed
	menusToUpdate[TRANSLATION_STATUS_MENU] = chosenOption;
	
	
}

/// <summary>
/// Toggles the choosen polygon's state and sets a flag to update the menu entry
/// </summary>
/// <param name="chosenOption">Polygon to update</param>
void HelloGL::RotationsMenu(int chosenOption)
{
	printf("Chosen Translation option: %i", chosenOption);
	linkedPolygonList->GetNode(head, chosenOption)->data->ToggleTranformation(Polygon3D::ROTATION);

	//changes the value of the menu update map to reflect that the choosen polygon needs its entry changed
	menusToUpdate[ROTATION_STATUS_MENU] = chosenOption;


}

/// <summary>
/// Creates a new title for the menu entry depending on the passed in state
/// </summary>
/// <param name="polygonID">The polygon assigned to the entry</param>
/// <param name="isActive">The current state to reflect</param>
/// <returns>The formated text stating the current state of the passed in polygon index</returns>
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


/// <summary>
/// Updates the translation menu to show the current translation status of the polygon
/// </summary>
/// <param name="polygonID">Polygon item to update</param>
void HelloGL::ChangeMenuStatus(const Menus menu, const int polygonID)
{
	std::string newTranslationStatus = "";
	switch (menu)
	{
	case TRANSLATION_STATUS_MENU:
	{
		newTranslationStatus = CreateTranformationMenuText(polygonID, linkedPolygonList->GetNode(head, polygonID)->data->GetTranslationStatus());
		break;
	}
	case ROTATION_STATUS_MENU:
	{
		newTranslationStatus = CreateTranformationMenuText(polygonID, linkedPolygonList->GetNode(head, polygonID)->data->GetRotationStatus());
		break;
	}
	default:
		break;
	}
	

	//changes the menu pointer to point to the translation menu and updates the text of the desired polygon menu entry
	glutSetMenu(menuIDs[menu]);
	glutChangeToMenuEntry(polygonID + 1, newTranslationStatus.c_str(), polygonID);
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

	for (int i = 0; i < linkedPolygonList->Size(); i++)
	{
		linkedPolygonList->GetNode(head, i)->data->Draw();
		//polygonList[i]->Draw();
	}
	
	
	bottomText->DrawString(newAnnouncement, {-0.4f, -0.4f, 0.0f});
	//annoucementText->DrawString(newAnnouncement, { 0.0f, 0.0f, 0.0f });

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

	std::string newUpdateText = "Shape ";
	int index = 0;
	bool hasStateBeenChanged = false;

	for (auto& menu : menusToUpdate)
	{
		if (menu.second != -1)
		{
			hasStateBeenChanged = true;
			switch (menu.first)
			{
			case TRANSLATION_STATUS_MENU:
				newUpdateText += std::to_string(menu.second) + " : " + linkedPolygonList->GetNode(head, menu.second)->data->GetPolygonName() + "'s Auto Translation is now ";
				switch (linkedPolygonList->GetNode(head, menu.second)->data->GetTranslationStatus())
				{
				case true:
					newUpdateText += "ON.";
					break;

				case false:
					newUpdateText += "OFF.";
					break;

				default:
					break;
				}

				break;

			case ROTATION_STATUS_MENU:
				newUpdateText += std::to_string(menu.second) + " : " + linkedPolygonList->GetNode(head, menu.second)->data->GetPolygonName() + "'s Auto Rotation is now ";

				switch (linkedPolygonList->GetNode(head, menu.second)->data->GetTranslationStatus())
				{
				case true:
					newUpdateText += "ON.";
					break;

				case false:
					newUpdateText += "OFF.";
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}

			

			ChangeMenuStatus(menu.first, menu.second);
			menu.second = -1;
		}

		index++;
	}

	if (hasStateBeenChanged)
	{
		newAnnouncement = newUpdateText;
	}
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

///// <summary>
///// Returns the vector index of the provided polygon
///// </summary>
///// <param name="polygon">The polygon to find</param>
///// <returns>The index of the polygon (returns -1 if not found)</returns>
//int HelloGL::FindPolygonInList(Polygon3D* polygon)
//{
//	int indexLocation = -1;
//
//	for (int i = 0; i < polygonList.size(); i++)
//	{
//		//if (polygonList[i].get() == polygon)
//		if (polygonList[i] == polygon)
//		{
//			indexLocation = i;
//		}
//	}
//
//	return indexLocation;
//}


///// <summary>
///// Deletes the given polygon from the system
///// </summary>
///// <param name="polygon">The polygon to be deleted</param>
//void HelloGL::DeletePolygon(Polygon3D* polygon)
//{
//	int oldLocation = FindPolygonInList(polygon);
//
//	delete polygon;
//	polygon = nullptr;
//
//	polygonList.erase(polygonList.begin() + oldLocation); //removes the deleted polygon from the vector list
//	
//}
