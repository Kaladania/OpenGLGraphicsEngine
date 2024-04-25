#pragma once

#include "Polygon3D.h"

class Teapot : public Polygon3D
{
public:
	Teapot(Vector3D scale = Vector3D(1, 1, 1), float translationSpeed = 0, float newRotationSpeed = 0);
	Teapot(float scale = 1, float translationSpeed = 0, float newRotationSpeed = 0);
	~Teapot();
};

