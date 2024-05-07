#include "Text.h"
#include "Header.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"

Text::Text()
{
	material.ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.shininess = 100.0f;
}

Text::~Text()
{

}

void Text::DrawString(std::string text, Vector3D position)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(material.ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material.diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(material.specular.x));

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRasterPos2f(0.0f, 0.0f);
	//glColor3f(color.x, color.y, color.z);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str());
	glPopMatrix();
}

void Text::ChangeMaterial(Material newMaterial)
{
	material.ambient = newMaterial.ambient;
	material.diffuse = newMaterial.diffuse;
	material.specular = newMaterial.specular;
	material.shininess = newMaterial.shininess;
}