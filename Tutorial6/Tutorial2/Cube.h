#pragma once
#ifndef _CUBE
#define _CUBE

#include "Polygon3D.h"

class Cube : public Polygon3D
{
protected:
	std::vector<Vector3D> vertexList = {
		Vector3D(1,1,1), Vector3D(-1, 1, 1), Vector3D(-1, -1, 1),
		Vector3D(-1, -1, 1), Vector3D(1, -1, 1), Vector3D(1, 1, 1),
		Vector3D(1, 1, 1), Vector3D(1, -1, 1), Vector3D(1, -1, -1),
		Vector3D(1, -1, -1), Vector3D(1, 1, -1), Vector3D(1, 1, 1),
		Vector3D(1, 1, 1), Vector3D(1, 1, -1), Vector3D(-1, 1, -1),
		Vector3D(-1, 1, -1), Vector3D(-1, 1, 1), Vector3D(1, 1, 1),
		Vector3D(-1, 1, 1), Vector3D(-1, 1, -1), Vector3D(-1, -1, -1),
		Vector3D(-1, -1, -1), Vector3D(-1, -1, 1), Vector3D(-1, 1, 1),
		Vector3D(-1, -1, -1), Vector3D(1, -1, -1), Vector3D(1, -1, 1),
		Vector3D(1, -1, 1), Vector3D(-1, -1, 1), Vector3D(-1, -1, -1),
		Vector3D(1, -1, -1), Vector3D(-1, -1, -1), Vector3D(-1, 1, -1),
		Vector3D(-1, 1, -1), Vector3D(1, 1, -1), Vector3D(1, -1, -1)
	}; //polygon vertex locations

public:
	Cube(Vector3D scale, Vector3D rotationSpeed = 0);
	Cube(float scale, Vector3D rotationSpeed = 0);

	virtual void Draw() override;
	void SetUpVertices();
	//virtual void AddVertices() override;

	/*void ScalePolygon(Vector3D scale);
	void ScalePolygon(float scale);*/
};

#endif // !_CUBE