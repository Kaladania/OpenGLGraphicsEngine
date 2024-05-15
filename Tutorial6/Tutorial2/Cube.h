#pragma once
#ifndef _CUBE
#define _CUBE

#include "Polygon3D.h"

class Cube : public Polygon3D
{
protected:


public:
	Cube(Vector3D scale = Vector3D(1, 1, 1), float translationSpeed = 0, float newRotationSpeed = 0, Textures chosenTexture = PENGUINS);
	Cube(float scale = 1, float translationSpeed = 0, float newRotationSpeed = 0, Textures chosenTexture = PENGUINS);

};

#endif // !_CUBE