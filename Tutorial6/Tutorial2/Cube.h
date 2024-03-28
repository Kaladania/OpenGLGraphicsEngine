#pragma once
#ifndef _CUBE
#define _CUBE
#include "Polygon.h"

class Cube : public Polygon
{
private:
	int sides = 8; //number of sides in cube
	int vertexAmount = 8; //number of vertices in polygon
	std::array<Vector3D, 8> vertices; //polygon vertex locations

public:
	Cube(int sides, int vertices);

	virtual void Draw() override;
	//virtual void AddVertices() override;
};

#endif // !_CUBE