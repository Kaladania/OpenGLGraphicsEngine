#pragma once
#ifndef _CUBE
#define _CUBE

#include "Polygon3D.h"

class Cube : public Polygon3D
{
protected:


public:
	Cube(Vector3D scale = Vector3D(1, 1, 1), float translationSpeed = 0, float newRotationSpeed = 0);
	Cube(float scale = 1, float translationSpeed = 0, float newRotationSpeed = 0);

	//virtual void Draw() override;
	//virtual void AddVertices() override;

	/*void ScalePolygon(Vector3D scale);
	void ScalePolygon(float scale);*/
};

#endif // !_CUBE