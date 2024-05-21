#include "Text.h"
#include "Header.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"

Text::Text(void* attribute, std::array<float, 4>& colorArray)
{
	material.ambient = { 1.4f, 1.4f, 1.4f, 1.4f };
	material.diffuse = { 1.4f, 1.4f, 1.4f, 1.4f };
	material.specular = { 1.4f, 1.4f, 1.4f, 1.4f };
	material.shininess = 400.0f;

	textAttribute = attribute;
	this->colorArray = colorArray;
}

Text::~Text()
{

}

void Text::DrawString(std::string text, Vector3D position)
{
	glDisable(GL_LIGHTING); //stops lighting from affecting colour of text
	glEnable(GL_COLOR); //enables colour so that text can be given an RGB colour value
	glMatrixMode(GL_PROJECTION); //sets matrix mode to projection to customise viewport

	glPushMatrix();
	glLoadIdentity(); //resets the matrix
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1,1); //sets the dimensions of the viewport
	glMatrixMode(GL_MODELVIEW); //sets matrix mode to projectile to customise object

	glPushMatrix();
	glLoadIdentity(); //resets the matrix
	
	glTranslatef(position.x, position.y, position.z); //renders text at given position
	glColor4f(colorArray[0], colorArray[1], colorArray[2], colorArray[3]); // renders text with the given colour

	glBindTexture(GL_TEXTURE_2D, 0); //sets a default texture to prevent colours from being influeced by shape textures

	glRasterPos2f(0.0f, 0.0f); //sets the inital position to bottom-right origin point
	glutBitmapString(textAttribute, (unsigned char*)text.c_str()); //renders text

	glColor3f(0, 0, 0); //resets colour back to black

	glPopMatrix(); //pops translation matrix
	glMatrixMode(GL_PROJECTION);

	glPopMatrix(); //pops Ortho matrix
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_COLOR); //disbales colour so scene can function as normal
	glEnable(GL_LIGHTING); //re-enables lightning so that objects can continue to be illuminated
}

void Text::ChangeMaterial(Material newMaterial)
{
	material.ambient = newMaterial.ambient;
	material.diffuse = newMaterial.diffuse;
	material.specular = newMaterial.specular;
	material.shininess = newMaterial.shininess;
}