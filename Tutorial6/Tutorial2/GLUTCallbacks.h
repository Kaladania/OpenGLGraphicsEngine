#pragma once

class HelloGL; //forward declaration to allow access to class

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);
	void Display();
	void GameTimer(int prefferedRefresh);
	void Keyboard(unsigned char key, int x, int y);

	void PolygonMenu(int chosenOption);
	void ToggleMenu(int chosenOption);
	void TransformationsMenu(int chosenOption);
	void TranslationsMenu(int chosenOption);
	void RotationsMenu(int chosenOption);
	void AddRemoveMenu(int chosenOption);
	void AddPolygonMenu(int chosenOption);
	void RemovePolygonMenu(int chosenOption);
	void BackgroundColourMenu(int chosenOption);
	void TrackingMenu(int chosenOption);
	void MaterialMenu(int chosenOption);
}