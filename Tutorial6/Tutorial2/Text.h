#pragma once
#include "Header.h"

#include <string>

//class Material;
struct Vector3D;
struct Vector4D;
struct Material;

/// <summary>
/// Class for creating text instances that can render text to the screen
/// </summary>
class Text
{
private:

	Material material; //material for text coloring/response to lightning
	//Vector3D position;
	//Vector3D color;

public:

	Text();
	~Text();

	void DrawString(std::string text, Vector3D position);
	void ChangeMaterial(Material newMaterial);

};

