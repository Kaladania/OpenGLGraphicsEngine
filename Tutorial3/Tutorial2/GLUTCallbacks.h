#pragma once

class HelloGL; //forward declaration to allow access to class

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);
	void Display();
	void GameTimer(int prefferedRefresh);
}