#include "HelloGL.h"
#include <tuple>

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this); //sets the current gl instance pointer to this current instance
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800); // creates a 800x800 window
	glutCreateWindow("Simple OpenGL Program"); //window title
	glutDisplayFunc(GLUTCallbacks::Display); //draws window
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{

}

float HelloGL::SetColor(colorCodes color, std::array<float, 4> &colorArray)
{
	//float colorCode[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	switch (color)
	{
	case RED:
		colorArray[0] = 1.0f;
		colorArray[1] = 0.0f;
		colorArray[2] = 0.0f;
		colorArray[3] = 0.0f;
		break;

	case YELLOW:
		return (1.0f, 1.0f, 0.0f, 0.0f);
		break;
	case GREEN:
		return (0.0f, 1.0f, 0.0f, 0.0f);
		break;
	case LIGHTBLUE:
		return (0.0f, 1.0f, 1.0f, 1.0f);
		break;
	case DARKBLUE:
		return (0.0f, 0.0f, 1.0f, 0.0f);
		break;
	case PURPLE:
		return (1.0f, 0.0f, 1.0f, 0.0f);
		break;
	case BLACK:
		return (0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case WHITE:
		return (1.0f, 1.0f, 1.0f, 0.0f);
		break;
	default:
		return(1.0f, 1.0f, 1.0f, 0.0f);
		break;
	}
}


/// <summary>
/// Draws objects into the scene
/// </summary>
void HelloGL::Display()
{
	std::array<float, 4> colorCode = { 1.0f, 0.0f, 0.0f, 0.0f};
	std::tuple<float, float> point1;
	std::tuple<float, float> point2;
	std::tuple<float, float> point3;
	std::tuple<float, float> point4;

	float triangleCoordinates[3][2];
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	//float triangleCoordinates[3][2] = { { 0, 0.5 }, { -0.75, -0.5 }, { 0.75, -0.5 } };

	//colorCode[0] = 
	DrawTriangle(SetColor(RED, colorCode));
	
	glFlush(); //flushes scene drawn to graphics card (draws polygon on the screen)
}

/// <summary>
/// Draws a preset rectangle
/// </summary>
/// <param name="r">red value</param>
/// <param name="g">blue value</param>
/// <param name="b">green value</param>
/// <param name="a">alpha value</param>
void HelloGL::DrawPolygon(float r, float g, float b, float a)
{

	glColor4f(r, g, b, a); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(-0.75, 0.5); //defines 1st point of polygon (top left)
		glVertex2f(0.75, 0.5); //defines 2nd point of polygon (top right)

		glVertex2f(0.75, -0.5); //defines 3rd point of polygon (bottom left)
		glVertex2f(-0.75, -0.5); //defines 4th point of polygon (bottom right)
		glEnd(); //stops drawing polygon (stops listening for instructions
	}
	
}


void HelloGL::DrawTriangle(std::array<float, 4>& colorCode, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
{
	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(0, -0.5); //defines 1st point of triangle
		glVertex2f(-0.75, 0.5); //defines 2nd point of triangle
		glVertex2f(0.75, 0.5); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

}