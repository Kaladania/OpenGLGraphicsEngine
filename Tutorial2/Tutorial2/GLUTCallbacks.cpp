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
}