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

struct Vector4D
{
	union { //allows iterative access to axises
		struct {
			float x; //rotation on x axis
			float y; //rotation on y axis
			float z; //rotation on z axis
			float w; //rotation on w axis
		};
		float axis[4];
	};

	/// <summary>
	/// Constructor (defaults to 0 if axis value is not given)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector4D(float x = 0, float y = 0, float z = 0, float w = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	///OPERATOR OVERRIDES//
	//Allows for Vector and Scalar Maths


	Vector4D operator * (Vector4D scale)
	{
		Vector4D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;
		temp.w = this->w;

		temp.x = this->x * scale.x;
		temp.y = this->y * scale.y;
		temp.z = this->z * scale.z;
		temp.w = this->w * scale.w;

		return temp;
	}

	Vector4D operator * (float scale)
	{
		Vector4D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;
		temp.w = this->w;

		temp.x = this->x * scale;
		temp.y = this->y * scale;
		temp.z = this->z * scale;
		temp.w = this->w * scale;

		return temp;
	}



	Vector4D operator + (Vector4D scale)
	{
		Vector4D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;
		temp.w = this->w;

		temp.x = this->x + scale.x;
		temp.y = this->y + scale.y;
		temp.z = this->z + scale.z;
		temp.w = this->w + scale.w;

		return temp;
	}

	Vector4D operator + (float scale)
	{
		Vector4D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;
		temp.w = this->w;

		temp.x = this->x + scale;
		temp.y = this->y + scale;
		temp.z = this->z + scale;
		temp.w = this->w + scale;

		return temp;
	}


	Vector4D operator - (Vector4D scale)
	{
		Vector4D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;
		temp.w = this->w;

		temp.x = this->x - scale.x;
		temp.y = this->y - scale.y;
		temp.z = this->z - scale.z;
		temp.w = this->w - scale.w;

		return temp;
	}

	Vector4D operator - (float scale)
	{
		Vector4D temp;
		temp.x = this->x;
		temp.y = this->y;
		temp.z = this->z;
		temp.w = this->w;

		temp.x = this->x - scale;
		temp.y = this->y - scale;
		temp.z = this->z - scale;
		temp.w = this->w + scale;

		return temp;
	}


	bool operator > (Vector4D scale)
	{
		return (this->x > scale.x && this->y > scale.y && this->z > scale.z && this->w > scale.w);
	}

	bool operator > (float scale)
	{

		return (this->x > scale && this->y > scale && this->z > scale && this->w > scale);
	}


	bool operator < (Vector4D scale)
	{
		return (this->x < scale.x && this->y < scale.y && this->z < scale.z && this->w < scale.w);
	}

	bool operator < (float scale)
	{

		return (this->x < scale && this->y < scale && this->z < scale && this->w < scale);
	}
};




struct Camera //camera structure
{
	Vector3D eye, center, up;
};

struct Material
{
	Vector4D ambient; // strength ambient light has on the material
	Vector4D diffuse; // strength diffuse light has on the material
	Vector4D specular; // strength specular light has on the material
	
	float shininess = 0.0f; //shininess of the material
};

struct Lighting
{
	Vector4D ambient; // strength of ambient light
	Vector4D diffuse; // strength of diffuse light
	Vector4D specular; // strength of specular light 

	Vector4D position; //position of light
};
