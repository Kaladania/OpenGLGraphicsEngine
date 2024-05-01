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
}