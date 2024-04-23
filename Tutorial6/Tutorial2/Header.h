#pragma once
#include <array>

//#define RED_MATERIAL Materia

struct Vector3D
{
	union { //allows iterative access to axises
		struct {
			float x; //rotation on x axis
			float y; //rotation on y axis
			float z; //rotation on z axis
		};
		float axis[3];
	};

	/// <summary>
	/// Constructor (defaults to 0 if axis value is not given)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector3D(float x = 0, float y = 0, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	///OPERATOR OVERRIDES//
	//Allows for Vector and Scalar Maths


	Vector3D operator * (Vector3D scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x * scale.x;
		temp.y = this->y * scale.y;
		temp.z = this->z * scale.z;

		return temp;
	}

	Vector3D operator * (float scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x * scale;
		temp.y = this->y * scale;
		temp.z = this->z * scale;

		return temp;
	}



	Vector3D operator + (Vector3D scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x + scale.x;
		temp.y = this->y + scale.y;
		temp.z = this->z + scale.z;

		return temp;
	}

	Vector3D operator + (float scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x + scale;
		temp.y = this->y + scale;
		temp.z = this->z + scale;

		return temp;
	}


	Vector3D operator - (Vector3D scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x - scale.x;
		temp.y = this->y - scale.y;
		temp.z = this->z - scale.z;

		return temp;
	}

	Vector3D operator - (float scale)
	{
		Vector3D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;

		temp.x = this->x - scale;
		temp.y = this->y - scale;
		temp.z = this->z - scale;

		return temp;
	}


	bool operator > (Vector3D scale)
	{
		return (this->x > scale.x && this->y > scale.y && this->z > scale.z);
	}

	bool operator > (float scale)
	{

		return (this->x > scale && this->y > scale && this->z > scale);
	}


	bool operator < (Vector3D scale)
	{
		return (this->x < scale.x && this->y < scale.y && this->z < scale.z);
	}

	bool operator < (float scale)
	{

		return (this->x < scale && this->y < scale && this->z < scale);
	}
};

struct Camera //camera structure
{
	Vector3D eye, center, up;
};

struct Material
{
	std::array<float, 4> ambient = {0.0f, 0.0f, 0.0f, 0.0f};
	std::array<float, 4> diffuse = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::array<float, 4> specular = { 0.0f, 0.0f, 0.0f, 0.0f };

	float shininess = 0.0f;
};

struct Lighting
{
	std::array<float, 4> red = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::array<float, 4> green = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::array<float, 4> blue = { 0.0f, 0.0f, 0.0f, 0.0f };

	std::array<float, 4> position = { 0.0f, 0.0f, 0.0f, 0.0f };
};
