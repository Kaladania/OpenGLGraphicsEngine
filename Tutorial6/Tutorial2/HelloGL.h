#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"

#include "Text.h"
#include "LinkedList.h"


#include <array>
#include <tuple>
#include <map>
#include <string>
#include <vector>
#include <memory>
//#include "Header.h"
//#define REFRESH_RATE 16
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

//class Material;
class Polygon3D;
struct Camera;
struct Lighting;
struct Vector3D;
//class Cube;
struct Transformation
{
	float translation;
	float rotation;
	float scale;
};

//struct CameraParent
//{
//	bool isParented = false;
//	Vector3D parentPosition;
//};

//struct MenuUpdateNeed
//{
//	//union { //allows iterative access to axises
//	//	struct {
//	//		int TranslationMenu = -1;; //rotation on x axis
//	//		//float y; //rotation on y axis
//	//		//float z; //rotation on z axis
//	//	};
//	//	float menus[1];
//	//};
//	//
//	int translationMenu = -1;; //rotation on x axis
//	int maxNumOfMenus = 1;
//	//		//float y; //rotation on y axis
//	//		//float z; //rotation on z axis
//
//};

class HelloGL
{
private:

	int refreshRate = 16; //current scene refresh rate
	float polygonRotation = 0.0f;//current polygon rotation
	float polygonRotationSpeed = 0.7f;
	float triangleRotation = 0.0f;

	std::array<float, 4> colorCode = { 1.0f, 0.0f, 0.0f, 0.0f }; //Array of RGBA values for current color
	std::tuple<float, float> vertex1; //position of 1st vertex of triangle
	std::tuple<float, float> vertex2; //position of 2nd vertex of triangle
	std::tuple<float, float> vertex3; //position of 3rd vertex of triangle
	std::tuple<float, float> vertex4;  //position of 4th vertex of triangle

	std::tuple<float, float, float> rotationAxis = std::make_tuple(0.0f, 0.0f, -1.0f);
	std::tuple<float, float, float> translationAxis = std::make_tuple(0.0f, 0.0f, 0.0f);

	//std::vector<std::shared_ptr<Polygon3D>> polygonList;//list of all drawn polygons
	//std::vector<Polygon3D* > polygonList;//list of all drawn polygons

	Polygon3D* selectedPolygon = nullptr;

	int polygonIndex = 0;

	Camera* camera; //current camera view

	Lighting* lighting; //current light source

	//std::string textureEnumStrings[END_OF_TEXTURE_ENUM] = { "Penguins, Stars" };
	//std::map <Textures, std::string> textureEnumToString = { {PENGUINS, "Penguins"}, {STARS, "Stars"} };

	enum Menus;
	std::map <Menus, int> menuIDs = { {POLYGON_MENU, 0}, {TOGGLE_MENU, 0}, {TRANSFORMATION_MENU, 0} };
	
	Text* updateText = nullptr;
	Text* dataText = nullptr;
	Text* cameraPosText = nullptr;
	Text* controlText = nullptr;

	std::string newAnnouncement = "";
	std::string dataToShow = "";
	std::string newCameraPosition = "";


	std::map<Menus, int> menusToUpdate; //dictionary of menus needing to be updated for that frame and the value to update them to
	
	LinkedList* linkedPolygonList = new LinkedList();
	ListNode* head = nullptr;

	int polygonMenuAmount = 0; //holds the amount of polygons current being shown in Polygon Menu

	//CameraParent cameraParent;

	Polygon3D* cameraParent = nullptr;

	/*std::map<Color, std::array<float, 4>> enumToColorArray =
	{ {RED, {1.0f, 0.0f, 0.0f, 0.0f}}, {ORANGE, {1.0f, 0.5f, 0.0f, 0.0f}}, {BLACK, {0.0f, 0.0f, 0.0f, 0.0f}} };*/

	std::array<float, 4> backgroundColorArray;

	bool showControls = true;



public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void); //class destructor

	//Types of Meshes currently availble to draw
	enum Meshes
	{
		CUBE,
		PYRAMID,
		TEAPOT,
		END_OF_MESH_ENUM
	};

	

	enum Menus
	{
		MAIN_MENU,
		POLYGON_MENU,
		TOGGLE_MENU,
		TRANSFORMATION_MENU,
		ADD_REMOVE_MENU,
		ADD_SHAPE_MENU,
		REMOVE_SHAPE_MENU,
		MATERIAL_MENU,
		TRANSLATION_STATUS_MENU,
		ROTATION_STATUS_MENU,
		SCALING_STATUS_MENU,
		VISIBILITY_STATUS_MENU,
		BACKGROUND_COLOUR_MENU,
		TRACKING_MENU,
		
		END_OF_MENU_ENUM
	};


	enum Color
	{
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		LIGHTBLUE,
		DARKBLUE,
		PURPLE,
		BLACK,
		WHITE,
		END_OF_COLOR_ENUM

	};

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitMenu();

	Polygon3D* CreateNewPolygon(Meshes newPolygon);

	void PolygonMenu(int option);

	void ToggleMenu(int option);
	void TransformationsMenu(int option);
	void TranslationsMenu(int option);
	void RotationsMenu(int option);
	void MaterialMenu(int chosenOption);

	void AddPolygon(Meshes newPolygon);

	void ChangeBackgroundColour(Color chosenColor);

	void SetObjectTracking(int chosenOption);

	std::string CreateTranformationMenuText(const int polygonID, const bool isActive);
	void ChangeMenuStatus(const Menus menu, const int polygonID);

	Transformation SanitiseTransformation(Transformation newMeshTransform);

	void SetColor(const Color color, std::array<float, 4>& colorArray);

	
	////void SetColor(std::array<float, 4>& colorArray);
	//void DrawQuadrilateral(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3, const std::tuple<float, float>& vertex4);
	//void DrawFreeTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3);
	//void DrawEqualTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength);
	//void DrawRightTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength);
	//void DrawIsoTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength, const float bottomLength);

	//void DrawEqualPolygon(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const int numberOfSides, const float sideLength, const std::tuple<float, float, float>& rotationAxis, const float rotationSpeed);

	//void Draw3D();
	void Display();
	void Update();

	void Keyboard(unsigned char key, int x, int y);
	float UpdateRotation(float rotation, float rotationSpeed);

	//void ShowAllShapeData();
	void UpdateShapeDataText();
	void UpdateCameraPosText();
	//void UpdateCameraPosition();
	//Vector3D UpdateRotation(Vector3D rotation, Vector3D rotationSpeed);

	//int FindPolygonInList(Polygon3D* polygon);
	//void DeletePolygon(Polygon3D* polygon);

	//void SetLight(Lighting* light, int ID);
};

