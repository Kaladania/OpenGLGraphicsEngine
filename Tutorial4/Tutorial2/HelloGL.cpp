#include "HelloGL.h"
#include "Header.h"



HelloGL::HelloGL(int argc, char* argv[])
{
	polygonRotation = 0.0f;

	GLUTCallbacks::Init(this); //sets the current gl instance pointer to this current instance
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); //enables double buffering
	glutInitWindowSize(800, 800); // creates a 800x800 window
	glutInitWindowPosition(100, 100); //alters the window - to - shape - drawing ratio
	glutCreateWindow("Simple OpenGL Program"); //window title
	glutDisplayFunc(GLUTCallbacks::Display); //draws window
	glutTimerFunc(refreshRate, GLUTCallbacks::GameTimer, refreshRate);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{

}

/// <summary>
/// Returns an array of color values
/// </summary>
/// <param name="color">The color being requested</param>
/// <param name="colorArray">Array of float values representing R, G, B and A</param>
void HelloGL::SetColor(const colorCodes color, std::array<float, 4> &colorArray)
{
	switch (color)
	{
	case RED:
		colorArray[0] = 1.0f;
		colorArray[1] = 0.0f;
		colorArray[2] = 0.0f;
		colorArray[3] = 0.0f;
		break;

	case YELLOW:
		colorArray[0] = 1.0f;
		colorArray[1] = 1.0f;
		colorArray[2] = 0.0f;
		colorArray[3] = 0.0f;
		break;

	case GREEN:
		colorArray[0] = 0.0f;
		colorArray[1] = 1.0f;
		colorArray[2] = 0.0f;
		colorArray[3] = 0.0f;
		break;

	case LIGHTBLUE:
		colorArray[0] = 0.0f;
		colorArray[1] = 1.0f;
		colorArray[2] = 1.0f;
		colorArray[3] = 1.0f;
		break;

	case DARKBLUE:
		colorArray[0] = 0.0f;
		colorArray[1] = 0.0f;
		colorArray[2] = 1.0f;
		colorArray[3] = 0.0f;
		break;

	case PURPLE:
		colorArray[0] = 1.0f;
		colorArray[1] = 0.0f;
		colorArray[2] = 1.0f;
		colorArray[3] = 0.0f;
		break;

	case BLACK:
		colorArray[0] = 0.0f;
		colorArray[1] = 0.0f;
		colorArray[2] = 0.0f;
		colorArray[3] = 0.0f;
		break;

	case WHITE:
		colorArray[0] = 1.0f;
		colorArray[1] = 1.0f;
		colorArray[2] = 1.0f;
		colorArray[3] = 0.0f;
		break;

	default: //returns white if current color is not supported
		colorArray[0] = 1.0f;
		colorArray[1] = 1.0f;
		colorArray[2] = 1.0f;
		colorArray[3] = 0.0f;
		break;
	}
}


/// <summary>
/// Draws objects into the scene
/// </summary>
void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	float triangleCoordinates[3][2];

	vertex1 = std::make_tuple(-0.75f, 0.6f);
	vertex2 = std::make_tuple(-0.55f, 0.6f);
	vertex3 = std::make_tuple(-0.55f, 0.4f);
	vertex4 = std::make_tuple(-0.75f, 0.4f);

	rotationAxis = std::make_tuple(0.0f, 0.0f, -1.0f);

	
	//glPushMatrix(); //begins matrix calculation
	
	
	SetColor(RED, colorCode);
	DrawQuadrilateral(colorCode, vertex1, vertex2, vertex3, vertex4);

	SetColor(YELLOW, colorCode);
	vertex1 = std::make_tuple(-0.45f, 0.6f);
	vertex2 = std::make_tuple(-0.15f, 0.6f);
	vertex3 = std::make_tuple(-0.15f, 0.4f);
	vertex4 = std::make_tuple(-0.45f, 0.4f);
	DrawQuadrilateral(colorCode, vertex1, vertex2, vertex3, vertex4);

	SetColor(GREEN, colorCode);
	vertex1 = std::make_tuple(-0.05f, 0.4f);
	DrawEqualTriangle(colorCode, vertex1, 0.25f);


	//Drawing a polygon pic

	//polygonRotationSpeed = 0.5f;
	SetColor(DARKBLUE, colorCode);
	vertex1 = std::make_tuple(0.0f, 0.0f);
	DrawEqualPolygon(colorCode, vertex1, 6, 0.5f, rotationAxis, 1); //Draws a hexagon

	//polygonRotationSpeed = 1.0f;
	SetColor(PURPLE, colorCode);
	DrawEqualPolygon(colorCode, vertex1, 4, 0.5f, rotationAxis, 1); //Draws a hexagon

	//polygonRotationSpeed = 4.0f;
	SetColor(WHITE, colorCode);
	DrawEqualPolygon(colorCode, vertex1, 10, 0.4f, rotationAxis, 1); //Draws a hexagon

	//polygonRotationSpeed = 0.1f;
	SetColor(YELLOW, colorCode);
	DrawEqualPolygon(colorCode, vertex1, 5, 0.3f, rotationAxis, 1); //Draws a hexagon

	//polygonRotationSpeed = 0.0f;
	SetColor(RED, colorCode);
	DrawEqualPolygon(colorCode, vertex1, 3, 0.15f, rotationAxis, 1); //Draws a hexagon

	//glPopMatrix();
	
	glFlush(); //flushes scene drawn to graphics card (draws polygon on the screen)
	glutSwapBuffers();
}

/// <summary>
/// Main Game Loop
/// </summary>
void HelloGL::Update() 
{
	glutPostRedisplay(); //forces the scene to redraw itself
	
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd') 
	{
		polygonRotation += polygonRotationSpeed;

		if (polygonRotation >= 360.0f)
		{
			polygonRotation = 0.0f;
		}

		triangleRotation += 0.8f;

		if (triangleRotation >= 360.0f)
		{
			triangleRotation = 0.0f;
		}
	}
	
}




/// <summary>
/// Draws a preset rectangle
/// </summary>
/// <param name="r">red value</param>
/// <param name="g">blue value</param>
/// <param name="b">green value</param>
/// <param name="a">alpha value</param>
void HelloGL::DrawQuadrilateral(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3, const std::tuple<float, float>& vertex4)
{
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//begins matrix calculation
	//glTranslatef(0, 0, 0);
	float localRotation = polygonRotation;
	localRotation += polygonRotationSpeed * 1.0f;

	if (localRotation >= 360.0f)
	{
		localRotation = polygonRotationSpeed * 1.0f;
	}

	glRotatef(localRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of quadet
		glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2)); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex3), std::get<1>(vertex3)); //defines 3rd point of triangle
		glVertex2f(std::get<0>(vertex4), std::get<1>(vertex4)); //defines 3rd point of triangle
		glEnd(); //stops drawing polygon (stops listening for instructions
	}
	
	glPopMatrix();
}

/// <summary>
/// Draws a triangle of any size/angle relationship
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
void HelloGL::DrawFreeTriangle(std::array<float, 4>& colorCode, const std::tuple<float,float>& vertex1, const std::tuple<float, float>& vertex2, const std::tuple<float, float>& vertex3)
{
	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2)); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex3), std::get<1>(vertex3)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

}


/// <summary>
/// Draws an equilateral triangle
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1">Starting position of the triangle</param>
/// <param name="sideLength">Length of all sides</param>
void HelloGL::DrawEqualTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength)
{
	float heightX = std::get<0>(vertex1) + (sideLength / 2); //position's height point halfway between side length
	float heightY= std::get<1>(vertex1) + (sideLength * (sqrt(3) / 2)); //calulates height point's y position (triangle height)
	
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//begins matrix calculation
	//glTranslatef(0, 0, 0);
	/*float localRotation = polygonRotation;
	localRotation += polygonRotationSpeed * 2.0f;

	if (localRotation >= 360.0f)
	{
		localRotation = polygonRotationSpeed * 2.0f;
	}*/

	float localRotation = triangleRotation;
	localRotation += polygonRotationSpeed * 2.0f;

	if (localRotation >= 360.0f)
	{
		localRotation = polygonRotationSpeed * 2.0f;
	}


	glRotatef(localRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(heightX, heightY); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex1) + sideLength, std::get<1>(vertex1)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

	glPopMatrix();

}


/// <summary>
/// Draws a right angle triangle
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1"></param>
/// <param name="sideLength"></param>
void HelloGL::DrawRightTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength)
{

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1) + sideLength); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex1) + sideLength, std::get<1>(vertex1)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

}

/// <summary>
/// Draws and isoceles triangle
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1">Starting position of the triangle</param>
/// <param name="sideLength">Length of side</param>
/// <param name="bottomLength">Length of bottom</param>
void HelloGL::DrawIsoTriangle(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const float sideLength, const float bottomLength)
{
	float heightX = std::get<0>(vertex1) + (bottomLength / 2); //position's height point halfway between side length
	float heightY = std::get<1>(vertex1) + sqrtf((sideLength * sideLength - ((bottomLength * bottomLength) / 4))); //calulates height point's y position (triangle height)

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1)); //defines 1st point of triangle
		glVertex2f(heightX, heightY); //defines 2nd point of triangle
		glVertex2f(std::get<0>(vertex1) + bottomLength, std::get<1>(vertex1)); //defines 3rd point of triangle

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

}


/// <summary>
/// Draws a polygon with equal sides and angles
/// </summary>
/// <param name="colorCode">Color values for the current shape</param>
/// <param name="vertex1">Starting position of the triangle</param>
/// <param name="numberOfSides">Number of sides in polygon</param>
/// <param name="sideLength">Length of side</param>
void HelloGL::DrawEqualPolygon(std::array<float, 4>& colorCode, const std::tuple<float, float>& vertex1, const int numberOfSides, const float sideLength, const std::tuple<float, float, float>& rotationAxis, const float rotationSpeed)
{
	float pointX = 0.0f;
	float pointY = 0.0f;

	float polygonAngle = 360.0f / numberOfSides; //determines the internal angles of the sides

	
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//RotatePolygon(rotationAxis, rotationSpeed);

	glColor4f(colorCode[0], colorCode[1], colorCode[2], colorCode[3]); //sets brush color to red
	glBegin(GL_POLYGON); //starts drawing a polygon (starts listening for instructions)
	{
		for (int i = 0; i < numberOfSides; i++)
		{
			//Determines co-ordinates for next point
			pointX = sideLength * cos(2 * 3.14f * i / numberOfSides);
			pointY = sideLength * sin(2 * 3.14f * i / numberOfSides);

			//Uses the previous point as an offset to draw the next part of the polygon
			glVertex2f(std::get<0>(vertex1) + pointX, std::get<1>(vertex1) + pointY);
		}

		glEnd(); //stops drawing polygon (stops listening for instructions
	}

	//glTranslatef(std::get<0>(vertex1), std::get<1>(vertex1), 0.0f);
	glPopMatrix(); //begins matrix calculation

}


//void HelloGL::RotatePolygon(const std::tuple<float, float, float>& rotationAxis, const float rotationSpeed)
//{
//	 //begins matrix calculation
//	//glTranslatef(0, 0, 0);
//	polygonRotation += polygonRotationSpeed * rotationSpeed;
//
//	if (polygonRotation >= 360.0f)
//	{
//		polygonRotation = 0.0f;
//	}
//
//	glRotatef(polygonRotation, std::get<0>(rotationAxis), std::get<1>(rotationAxis), std::get<2>(rotationAxis)); //rotates the drawn polygon
//}