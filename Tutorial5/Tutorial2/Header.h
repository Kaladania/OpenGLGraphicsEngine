#pragma once

//struct Polygon
//{
//	Colo
//};

struct Vector3 //3D vector structure
{
	float x, y, z = 0.0f; //vector axis
};

struct Camera //camera structure
{
	Vector3 eye, center, up;
};

Camera* camera;


