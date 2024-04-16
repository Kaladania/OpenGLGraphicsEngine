#pragma once
class OLDVector3D
{
private:
	//union { //allows iterative access to axises
	//	struct {
	//		float x; //rotation on x axis
	//		float y; //rotation on y axis
	//		float z; //rotation on z axis
	//	};
	//	float axis[3];
	//};

	float x; //rotation on x axis
	float y; //rotation on y axis
	float z; //rotation on z axis

public:

	OLDVector3D(float x = 0, float y = 0, float z = 0);

	/*Vector3D operator * (Vector3D scale)
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
	}*/
};

