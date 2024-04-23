#include "Texture2D.h"
#include <fstream>
#include <iostream>
/// <summary>
/// Constructor
/// </summary>
Texture2D::Texture2D()
{

}

/// <summary>
/// Destructor
/// </summary>
Texture2D::~Texture2D()
{

}

/// <summary>
/// Loads in a new texture (RAW ONLY)
/// </summary>
/// <param name="path">file path to texture</param>
/// <param name="width">texture width</param>
/// <param name="height">texture height</param>
/// <returns></returns>
bool Texture2D::Load(std::string path, const int width, const int height)
{
	int fileSize = 0;
	//char* tempTextureData;
	this->width = width;
	this->height = height;

	//opens the specified texture
	//std::string filePath = "Textures/" + textureName + ".png";
	std::ifstream inFile;
	inFile.open(path, std::ios::binary);

	//displays error message if file failed to open
	if (!inFile.good())
	{
		std::cerr << "Can't open txt file:  " << path << std::endl;
		return false;
	}

	inFile.seekg(0, std::ios::end); //set pointer to end of file
	fileSize = (int)inFile.tellg(); //returns location of pointer (equivalient to file size)
	textureData = new char[fileSize]; //creates an appropriately sized array to store the contents of the file
	inFile.seekg(0, std::ios::beg); //sets pointer to beginning of file
	inFile.read(textureData, fileSize); //reads all the data in the file and stores each line to an array element
	inFile.close();

	std::cout << "\n" << path << " has been fully loaded." << std::endl;

	//generates a new texture
	glGenTextures(1, &textureID); //generates and assigns a new texture ID
	glBindTexture(GL_TEXTURE_2D, textureID); //binds the texture to the new ID
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData); //specifices texture image detail
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minifaction filter
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnification filter

	std::cout << "\n" << path << "has been binded." << std::endl;

	//delete [] tempTextureData;
	return true;
}