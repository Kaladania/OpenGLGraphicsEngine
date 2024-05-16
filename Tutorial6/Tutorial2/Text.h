#pragma once
#include "Header.h"

#include <string>
#include <array>

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

	void* textAttribute = nullptr;
	std::array<float, 4> colorArray;

public:

	Text(void* attribute, std::array<float, 4>& colorArray);
	~Text();

	void DrawString(std::string text, Vector3D position);
	void ChangeMaterial(Material newMaterial);

};

