#pragma once

#include "Polygon3D.h"

class Pyramid : public Polygon3D
{
protected:


public:
	Pyramid(Vector3D scale = Vector3D(1, 1, 1), float translationSpeed = 0, float newRotationSpeed = 0, Textures chosenTexture = PENGUINS);
	Pyramid(float scale = 1, float translationSpeed = 0, float newRotationSpeed = 0, Textures chosenTexture = PENGUINS);

};

