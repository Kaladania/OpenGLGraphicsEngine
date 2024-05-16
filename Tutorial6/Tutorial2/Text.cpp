#include "Text.h"
#include "Header.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include "freeglut.h"
#include "GLUTCallbacks.h"

Text::Text(void* attribute)
{
	material.ambient = { 1.4f, 1.4f, 1.4f, 1.4f };
	material.diffuse = { 1.4f, 1.4f, 1.4f, 1.4f };
	material.specular = { 1.4f, 1.4f, 1.4f, 1.4f };
	material.shininess = 400.0f;

	textAttribute = attribute;
}

Text::~Text()
{

}

void Text::DrawString(std::string text, Vector3D position)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(material.ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material.diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(material.specular.x));

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glTranslatef(position.x, position.y, position.z);
	glColor4f(1,1,1,1); // white

	glBindTexture(GL_TEXTURE_2D, 0);

	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(textAttribute, (unsigned char*)text.c_str());

	glColor3f(0, 0, 0);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_COLOR);
	glEnable(GL_LIGHTING);
}

void Text::ChangeMaterial(Material newMaterial)
{
	material.ambient = newMaterial.ambient;
	material.diffuse = newMaterial.diffuse;
	material.specular = newMaterial.specular;
	material.shininess = newMaterial.shininess;
}