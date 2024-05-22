#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks //creates free methods wrappers to allow FreeGLUT to access class methods
{
	namespace // annonymous namespace restricts write access to point to only code within namespace
	{
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl) //sets the pointer to the passed in class instance
	{
		helloGL = gl;
	}

	void Display() //calls the instance's display setup function
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void GameTimer(int prefferedRefresh) 
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME); //gets the amount of time it takes to start the timer/scene
		helloGL->Update();
		updateTime -= glutGet(GLUT_ELAPSED_TIME);
		glutTimerFunc(prefferedRefresh - updateTime, GLUTCallbacks::GameTimer, prefferedRefresh); //sets the frame rate offset by the start-up time
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}

	void PolygonMenu(int chosenOption)
	{
		helloGL->PolygonMenu(chosenOption);
	}

	void ToggleMenu(int chosenOption)
	{
		helloGL->ToggleMenu(chosenOption);
	}

	void TransformationsMenu(int chosenOption)
	{
		helloGL->TransformationsMenu(chosenOption);
	}

	void TranslationsMenu(int chosenOption)
	{
		helloGL->TranslationsMenu(chosenOption);
		//helloGL->ChangeMenuStatus(chosenOption);
	}

	void RotationsMenu(int chosenOption)
	{
		helloGL->RotationsMenu(chosenOption);
		//helloGL->ChangeMenuStatus(chosenOption);
	}

	void AddRemoveMenu(int chosenOption)
	{

	}

	void AddPolygonMenu(int chosenOption)
	{
		//converts the chosen option into a mesh enum to be generated
		helloGL->AddPolygon(HelloGL::Meshes(chosenOption));
	}

	void BackgroundColourMenu(int chosenOption)
	{
		helloGL->ChangeBackgroundColour(HelloGL::Color(chosenOption));
	}

	void TrackingMenu(int chosenOption)
	{
		helloGL->SetObjectTracking(chosenOption);
	}

	void MaterialMenu(int chosenOption)
	{
		helloGL->MaterialMenu(chosenOption);
	}
}