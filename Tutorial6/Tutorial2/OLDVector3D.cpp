#include "OLDVector3D.h"

/// <summary>
		/// Constructor (defaults to 0 if axis value is not given)
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
OLDVector3D::OLDVector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}