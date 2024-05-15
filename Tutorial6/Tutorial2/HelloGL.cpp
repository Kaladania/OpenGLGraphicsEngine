#include "HelloGL.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Header.h"
#include "Teapot.h"
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

	delete updateText;
	updateText = nullptr;

	delete cameraPosText;
	cameraPosText = nullptr;

	delete dataText;
	dataText = nullptr;

	delete selectedPolygon;
	selectedPolygon = nullptr;

	if (cameraParent != nullptr)
	{
		delete cameraParent;
		cameraParent = nullptr;
	}

	linkedPolygonList->DeleteList(&head);
	linkedPolygonList = nullptr;

	head = nullptr;
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

	

	//float newTranslation = 0;
	//float newScale = 0;
	//float newRotation = 0;

	//Meshes newMesh = CUBE;
	//Polygon3D::Textures newTexture = Polygon3D::PENGUINS;

	

	for (int i = 0; i < 5; i++)
	{
		CreateNewPolygon(END_OF_MESH_ENUM);
	}

	for (int i = 0; i < END_OF_MENU_ENUM; i++)
	{
		menusToUpdate[static_cast<Menus>(i)] = -1;
	}

	newAnnouncement = "Number of Polygons Loaded: " + std::to_string(linkedPolygonList->Size());

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

	glEnable(GL_LIGHTING); //enables lighting
	glEnable(GL_LIGHT0); //sets up 1st light

	glEnable(GL_TEXTURE_2D); //enables texture loading
	glEnable(GL_CULL_FACE); //enables backwards culling
	glCullFace(GL_BACK); //sets culling mode to backwards culling
}

/// <summary>
/// Initialises the simulation menu.
/// For enum menu entries, each entry is converted from the corrisponding enum value for accurate conversion
/// </summary>
void HelloGL::InitMenu()
{
	//creates a new menu to change the background colour
	menuIDs[BACKGROUND_COLOUR_MENU] = glutCreateMenu(GLUTCallbacks::BackgroundColourMenu);

	//adds menu entries providing options for the new background colour
	glutAddMenuEntry("Red", int(RED));
	glutAddMenuEntry("Orange", int(ORANGE));
	glutAddMenuEntry("Yellow", int(YELLOW));
	glutAddMenuEntry("Green", int(GREEN));
	glutAddMenuEntry("Light Blue", int(LIGHTBLUE));
	glutAddMenuEntry("Dark Blue", int(DARKBLUE));
	glutAddMenuEntry("Purple", int(PURPLE));
	glutAddMenuEntry("Black", int(BLACK));
	glutAddMenuEntry("White", int(WHITE));

	
	//creates a new menu to alter the selected object's current transformation
	menuIDs[TRANSFORMATION_MENU] = glutCreateMenu(GLUTCallbacks::TransformationsMenu);
	
	//adds menu entries providing options to toggle the object's current automations
	glutAddMenuEntry("Toggle Auto Translation", 0);
	glutAddMenuEntry("Toggle Auto Rotation", 1);
	glutAddMenuEntry("Toggle Visibility", 2);
	
	
	
	//creates a new menu to add new polygon objects to the simulation
	menuIDs[ADD_SHAPE_MENU] = glutCreateMenu(GLUTCallbacks::AddPolygonMenu);

	//adds menu entries providing options to specify which new object to load in
	glutAddMenuEntry("Add New Cube", int(CUBE));
	glutAddMenuEntry("Add New Pyramid", int(PYRAMID));
	glutAddMenuEntry("Add New Teapot", int(TEAPOT));


	
	//creates a new menu to choose wheither to add or remove a polygon from the current simulation
	menuIDs[ADD_REMOVE_MENU] = glutCreateMenu(GLUTCallbacks::AddRemoveMenu);

	//adds menu entries specifying wheither to add or remove a polygon
	//the decision to add a new polygon will lead to a sub-menu specifying the type
	glutAddSubMenu("Add New Polygon", menuIDs[ADD_SHAPE_MENU]);
	glutAddMenuEntry("Remove Selected Polygon", -1);



	//creates
	/*menuIDs[TOGGLE_MENU] = glutCreateMenu(GLUTCallbacks::ToggleMenu);

	glutAddSubMenu("Toggle Auto Transformations", menuIDs[TRANSFORMATION_MENU]);*/


	//creates a new menu specifying wheither to have the camera track the current selected polygon
	menuIDs[TRACKING_MENU] = glutCreateMenu(GLUTCallbacks::TrackingMenu);

	//adds menu entries specifying wheither to start or stop tracking
	glutAddMenuEntry("Start Tracking Selected Object", 0);
	glutAddMenuEntry("Stop Tracking Selected Object", 1);



	//creates a new sub menu specifying the current (all) polygon(s) the user is able to select from
	menuIDs[POLYGON_MENU] = glutCreateMenu(GLUTCallbacks::PolygonMenu);

	//adds all loaded polygons to the polygon menu
	std::string polygonName = "";
	for (int i = 0; i < linkedPolygonList->Size(); i++)
	{
		//format: Shape <shape ID> : <shape name>
		polygonName = "Shape " + std::to_string(i) + ": " + linkedPolygonList->GetNode(head, i)->data->GetPolygonName();
		
		glutAddMenuEntry(polygonName.c_str(), i);

		polygonMenuAmount++;
	}

	//creates a new sub menu specifying the materials the user can use to customise the selected polygon
	menuIDs[MATERIAL_MENU] = glutCreateMenu(GLUTCallbacks::MaterialMenu);

	//adds menu entries specifying the materials the user can select from
	glutAddMenuEntry("Penguins", int(Polygon3D::PENGUINS));
	glutAddMenuEntry("Stars", int(Polygon3D::STARS));


	//creates the main menu the user can use to interact with the simulation
	menuIDs[MAIN_MENU] = glutCreateMenu(GLUTCallbacks::ToggleMenu);
	
	//adds menu entries outlining the current operations the user can execute
	glutAddSubMenu("Select Shape", menuIDs[POLYGON_MENU]);
	glutAddSubMenu("Toggle Automatic Transformations", menuIDs[TRANSFORMATION_MENU]);
	glutAddSubMenu("Add/Remove Shape", menuIDs[ADD_REMOVE_MENU]);
	glutAddSubMenu("Change Shape Material", menuIDs[MATERIAL_MENU]);
	glutAddSubMenu("Change Background Color", menuIDs[BACKGROUND_COLOUR_MENU]);
	glutAddSubMenu("Track Selected Object", menuIDs[TRACKING_MENU]);

	//gives the user an easy way to back out of the menu
	glutAddMenuEntry("None", -2);

	//assigns the menu to load on right mouse click
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

/// <summary>
/// Loads in a new polygon with randomised translation, rotation, texture and scale
/// </summary>
/// <param name="newPolygon">The type of polygon to be created. END_OF_POLYGON_ENUM is used to assign a random polygon</param>
/// <returns>the newly created polygon</returns>
Polygon3D* HelloGL::CreateNewPolygon(Meshes newPolygon)
{

	Polygon3D::Textures newTexture = Polygon3D::PENGUINS; //holds the polygon's randomised texture

	float newTranslation = rand() % 10; //random number between 0.001 and 0.1
	newTranslation /= 1000;

	float newScale = rand() % 5; //random number between 0.001 and 0.1
	newScale /= 100;

	float newRotation = rand() % 10; //random number between 0.001 and 0.1


	//if no polygon was specified (polygon == END_OF_POLYGON_ENUM), chooses a random polygon to load
	if (newPolygon == END_OF_MESH_ENUM)
	{
		newPolygon = Meshes(rand() % END_OF_MESH_ENUM); //chooses a random mesh to load
	}

	newTexture = Polygon3D::Textures(rand() % Polygon3D::END_OF_TEXTURE_ENUM); //chooses a random mesh to load

	//creates a new transformation struct instance to pass randomised values into sanitation
	Transformation newMeshTransform;
	newMeshTransform.translation = newTranslation;
	newMeshTransform.rotation = newRotation;
	newMeshTransform.scale = newScale;

	SanitiseTransformation(newMeshTransform);

	//loads the new polygon using the correct constructor
	switch (newPolygon)
	{
	case HelloGL::CUBE:

		return linkedPolygonList->MakeNode(&head, new Cube(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, newTexture))->data;

	case HelloGL::PYRAMID:

		return linkedPolygonList->MakeNode(&head, new Pyramid(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation, newTexture))->data;

	case HelloGL::TEAPOT:

		return linkedPolygonList->MakeNode(&head, new Teapot(newMeshTransform.scale, newMeshTransform.translation, newMeshTransform.rotation))->data;

	default:
		break;
	}
}

/// <summary>
/// Sets the desired polygon to be the new selected shape
/// </summary>
/// <param name="chosenOption">ID of the new selected polygon</param>
void HelloGL::PolygonMenu(int chosenOption)
{
	if (chosenOption > -1 && chosenOption < linkedPolygonList->Size())
	{
		//format: Shape <shape ID> : <shape name> was chosen
		newAnnouncement = "Shape " + std::to_string(chosenOption) + ": " + linkedPolygonList->GetNode(head, chosenOption)->data->GetPolygonName() + " was chosen";
		selectedPolygon = linkedPolygonList->GetNode(head, chosenOption)->data;

		//updates the shape data preview text to show the toggle states of the new selected polygon
		UpdateShapeDataText();
	}
}


void HelloGL::ToggleMenu(int chosenOption)
{
	printf("Chosen Toggle option: %i", chosenOption);
}

/// <summary>
/// Toggles the desired transformation of the current selected polygon
/// </summary>
/// <param name="chosenOption">the transformation to toggle</param>
void HelloGL::TransformationsMenu(int chosenOption)
{
	if (selectedPolygon != nullptr)
	{
		//toggles the specified transformation and sends a notice that a new announcement text needs to be made
		switch (chosenOption)
		{
		case 0:

			selectedPolygon->ToggleTranformation(Polygon3D::TRANSLATION);
			menusToUpdate[TRANSLATION_STATUS_MENU] = linkedPolygonList->Find(head, selectedPolygon);
			break;

		case 1:

			selectedPolygon->ToggleTranformation(Polygon3D::ROTATION);
			menusToUpdate[ROTATION_STATUS_MENU] = linkedPolygonList->Find(head, selectedPolygon);
			break;

		case 2:

			selectedPolygon->ToggleTranformation(Polygon3D::VISIBILITY);
			menusToUpdate[VISIBILITY_STATUS_MENU] = linkedPolygonList->Find(head, selectedPolygon);
			break;

		default:
			break;
		}
	}
}

/// <summary>
/// Toggles the choosen polygon's state and sets a flag to update the menu entry
/// </summary>
/// <param name="chosenOption">Polygon to update</param>
void HelloGL::TranslationsMenu(int chosenOption)
{
	//printf("Chosen Translation option: %i", chosenOption);

	if (selectedPolygon != nullptr)
	{
		selectedPolygon->ToggleTranformation(Polygon3D::TRANSLATION);
		menusToUpdate[TRANSLATION_STATUS_MENU] = linkedPolygonList->Find(head, selectedPolygon);
	}
}

/// <summary>
/// Toggles the choosen polygon's state and sets a flag to update the menu entry
/// </summary>
/// <param name="chosenOption">Polygon to update</param>
void HelloGL::RotationsMenu(int chosenOption)
{
	//printf("Chosen Translation option: %i", chosenOption);
	//linkedPolygonList->GetNode(head, chosenOption)->data->ToggleTranformation(Polygon3D::ROTATION);

	////changes the value of the menu update map to reflect that the choosen polygon needs its entry changed
	

	if (selectedPolygon != nullptr)
	{
		selectedPolygon->ToggleTranformation(Polygon3D::ROTATION);
		menusToUpdate[ROTATION_STATUS_MENU] = linkedPolygonList->Find(head, selectedPolygon);
	}


}

/// <summary>
/// Creates a new requested polygon and adds it to the linked list
/// </summary>
/// <param name="chosenOption">chosen polygon</param>
void HelloGL::AddPolygon(Meshes newPolygon)
{
	//creates a new polygon based on the specified mesh
	switch (newPolygon)
	{
	case CUBE:
		selectedPolygon = CreateNewPolygon(CUBE);
		break;

	case PYRAMID:
		selectedPolygon = CreateNewPolygon(PYRAMID);
		break;

	case TEAPOT:
		selectedPolygon = CreateNewPolygon(TEAPOT);
		break;

	default:
		selectedPolygon = CreateNewPolygon(END_OF_MESH_ENUM);
		break;
	}

	//sets the selected polygon as the newly created polygon
	//selectedPolygon = linkedPolygonList->GetNode(head, linkedPolygonList->Size())->data;
	menusToUpdate[POLYGON_MENU] = 0;
}

/// <summary>
/// Changes the background colour to the given option
/// </summary>
/// <param name="chosenColor">new color of background</param>
void HelloGL::ChangeBackgroundColour(Color chosenColor)
{
	//updates the background color array with the new values of the specified color
	SetColor(Color(chosenColor), backgroundColorArray);

	//sets the background color to the new color
	glClearColor(backgroundColorArray[0], backgroundColorArray[1], backgroundColorArray[2], backgroundColorArray[3]);
}

/// <summary>
/// Parents/Deparents the camera to/from the current selected polygon
/// </summary>
/// <param name="chosenOption">object tracking state</param>
void HelloGL::SetObjectTracking(int chosenOption)
{
	switch (chosenOption)
	{
	case 0:

		//sets selected object to be the camera's new parent if there is currently an object selected
		if (selectedPolygon != nullptr)
		{
			//format: Shape <shape ID> is being tracked by camera
			newAnnouncement = "Shape " + std::to_string(linkedPolygonList->Find(head, selectedPolygon)) + "is being tracked by Camera";
			cameraParent = selectedPolygon;
		}

		break;

	case 1:

		//removes the camera's parent and resets it to its default position
		cameraParent = nullptr;
		camera->center.x = 0.0f;
		camera->center.y = 0.0f;
		camera->eye.z = 1.0f;
		newAnnouncement = "Camera is no longer tracking an object";
		break;

	default:
		break;
	}
}

/// <summary>
/// Changes the material of the current selected polygon
/// </summary>
/// <param name="chosenOption">the index of the new material</param>
void HelloGL::MaterialMenu(int chosenOption)
{
	//ensures that there is a polygon to change the material of
	if (selectedPolygon != nullptr)
	{
		//converts the index to a Texture enum and force the current selected polygon to load in the new texture
		switch (Polygon3D::Textures(chosenOption))
		{
		case Polygon3D::PENGUINS:

			selectedPolygon->LoadTextureFromFile(Polygon3D::PENGUINS);
			break;

		case Polygon3D::STARS:

			selectedPolygon->LoadTextureFromFile(Polygon3D::STARS);
			break;

		case Polygon3D::END_OF_TEXTURE_ENUM:
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// Converts bool states to their written ON/OFF counterparts
/// </summary>
/// <param name="polygonID">The polygon assigned to the entry</param>
/// <param name="isActive">the bool to convert</param>
/// <returns>The string translation</returns>
std::string HelloGL::CreateTranformationMenuText( const int polygonID, const bool isActive)
{
	std::string polygonStatus = "";

	switch (isActive)
	{
	case true:
		return "ON";

	case false:
		return "OFF";
	}
}


/// <summary>
/// Updates the polygon menu to show the current list of polygons
/// </summary>
/// <param name="polygonID">Polygon item to update</param>
void HelloGL::ChangeMenuStatus(const Menus menu, const int polygonID)
{
	std::string newTranslationStatus = "";
	switch (menu)
	{
	case POLYGON_MENU:

	{
		//sets the current menu to update to be the polygon menu
		glutSetMenu(menuIDs[POLYGON_MENU]);


		std::string polygonName = "";
		
		//updates all the current existing listings
		for (int i = 0; i < glutGet(GLUT_MENU_NUM_ITEMS); i++)
		{
			//format: Shape <shape ID> : <shape name>
			polygonName = "Shape " + std::to_string(i) + ": " + linkedPolygonList->GetNode(head, i)->data->GetPolygonName();

			//documentation states menu entries start from 1
			glutChangeToMenuEntry(i + 1, polygonName.c_str(), i);
		}

		//adds need new listings
		//glutGet(GLUT_MENU_NUM_ITEMS) == current amount of menu entries
		//determines amount of new entires needing to be added and runs for that duration
		for (int i = 0; i < linkedPolygonList->Size() - glutGet(GLUT_MENU_NUM_ITEMS); i++)
		{
			//format: Shape <shape ID> : <shape name>
			polygonName = "Shape " + std::to_string(glutGet(GLUT_MENU_NUM_ITEMS) + i) + ": " + linkedPolygonList->GetNode(head, glutGet(GLUT_MENU_NUM_ITEMS) + i)->data->GetPolygonName();
			
			glutAddMenuEntry(polygonName.c_str(), glutGet(GLUT_MENU_NUM_ITEMS) + i);
		}

		polygonMenuAmount = linkedPolygonList->Size();

		break;
	}
	
	default:
		break;
	}
	
}

/// <summary>
/// Ensures that translation, rotation and scale values are not 0
/// </summary>
/// <param name="newMeshTransform">struct of transforms to sanitise</param>
/// <returns>the sanitised struct of transforms</returns>
Transformation HelloGL::SanitiseTransformation(Transformation newMeshTransform)
{
	//Creates a cube with randomised properties
	if (newMeshTransform.translation == 0.000f)
	{
		newMeshTransform.translation = 0.0001f;
	}
	else if (newMeshTransform.scale == 0.00f)
	{
		newMeshTransform.scale = 0.01f;
	}
	else if (newMeshTransform.rotation == 0.0f)
	{
		newMeshTransform.rotation = 1.0f;
	}

	return newMeshTransform;

}

/// <summary>
/// Draws objects into the scene
/// </summary>
void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	//renders polygons to screen
	for (int i = 0; i < linkedPolygonList->Size(); i++)
	{
		//draws polygon if its visibility is enabled
		if (linkedPolygonList->GetNode(head, i)->data->GetToggleStatus(Polygon3D::VISIBILITY))
		{
			linkedPolygonList->GetNode(head, i)->data->Draw();
		}
	}
	
	//renders text objects to screen
	updateText->DrawString(newAnnouncement, {-0.4f, -0.4f, 0.0f});
	dataText->DrawString(dataToShow, {-0.4f, 0.38f, 0.0f});
	cameraPosText->DrawString(newCameraPosition, {-0.4f, 0.0f, 0.0f});

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

	//preps for menu entry update check
	std::string newUpdateText = "Shape ";
	std::string newDataText = "Shape ";
	int index = 0;
	bool hasStateBeenChanged = false;

	//loops through the update map and checks if any menu entries need to be updated
	for (auto& menu : menusToUpdate)
	{
		if (menu.second != -1)
		{
			hasStateBeenChanged = true;
			switch (menu.first)
			{

			case POLYGON_MENU:

				//ensures selected Polygon has a value before trying to access its name
				if (selectedPolygon != nullptr)
				{
					newUpdateText += std::to_string(linkedPolygonList->Size() - 1) + " : " + selectedPolygon->GetPolygonName() + "has been created";
				}
				
				break;

			case TRANSLATION_STATUS_MENU:
				newUpdateText += std::to_string(menu.second) + " : " + selectedPolygon->GetPolygonName() + "'s Auto Translation is now ";
				switch (linkedPolygonList->GetNode(head, menu.second)->data->GetToggleStatus(Polygon3D::TRANSLATION))
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
				newUpdateText += std::to_string(menu.second) + " : " + selectedPolygon->GetPolygonName() + "'s Auto Rotation is now ";
	
				switch (linkedPolygonList->GetNode(head, menu.second)->data->GetToggleStatus(Polygon3D::ROTATION))
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

			case VISIBILITY_STATUS_MENU:
				newUpdateText += std::to_string(menu.second) + " : " + selectedPolygon->GetPolygonName() + "'s Visibility is now ";

				switch (linkedPolygonList->GetNode(head, menu.second)->data->GetToggleStatus(Polygon3D::VISIBILITY))
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

	//updates the announcement and shape data text to reflect current actions and selections
	if (hasStateBeenChanged)
	{
		newAnnouncement = newUpdateText;
		UpdateShapeDataText();
	}

	//updates the camera position text to reflect the new position of the camera
	UpdateCameraPosText();

	//sets camera to follow selected objects position and zooms in on said object
	if (cameraParent != nullptr)
	{
		camera->center.x = cameraParent->GetPosition().x;
		camera->center.y = cameraParent->GetPosition().y;
		camera->eye.z = 0.5f;
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
	//enables keyboard input if the camera is not tracking an object
	if (cameraParent == nullptr)
	{

		switch (key)
		{
		case 'k':
			camera->center.x -= 0.1f;
			break;

		case ';':
			camera->center.x += 0.1f;
			break;

		case 'o':
			camera->center.y += 0.1f;
			break;

		case 'l':
			camera->center.y -= 0.1f;
			break;

		case 'i':
			camera->eye.z -= 0.5f;
			break;

		case 'p':
			camera->eye.z += 0.5f;
			break;

			/*case 'a':
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
				break;*/

		}
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

/// <summary>
/// Update displayed info of the current selected shape
/// </summary>
void HelloGL::UpdateShapeDataText()
{
	int polygonLocation = linkedPolygonList->Find(head, selectedPolygon);

	dataToShow = "Shape " + std::to_string(polygonLocation) + ": " + linkedPolygonList->GetNode(head, polygonLocation)->data->GetPolygonName()
		+ "\nAuto Translate: " + CreateTranformationMenuText(0, selectedPolygon->GetToggleStatus(Polygon3D::TRANSLATION))
		+ "\nAuto Rotate: " + CreateTranformationMenuText(0, selectedPolygon->GetToggleStatus(Polygon3D::ROTATION))
		+ "\nVisibility: " + CreateTranformationMenuText(0, selectedPolygon->GetToggleStatus(Polygon3D::VISIBILITY));
}

/// <summary>
/// Update displayed position info of the camera
/// </summary>
void HelloGL::UpdateCameraPosText()
{
	newCameraPosition = "Camera Position | X: " + std::to_string(camera->center.x)
		+ "Y: " + std::to_string(camera->center.y)
		+ "Z: " + std::to_string(camera->eye.z);
}



/// <summary>
/// Returns an array of color values
/// </summary>
/// <param name="color">The color being requested</param>
/// <param name="colorArray">Array of float values representing R, G, B and A</param>
void HelloGL::SetColor(const Color color, std::array<float, 4>& colorArray)
{
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