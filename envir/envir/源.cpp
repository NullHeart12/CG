// CGDemo.cpp : 定义控制台应用程序的入口点。
// CGDemo.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <GL/freeglut.h>              // glut.h includes gl.h and glu.h already
#include <ctype.h>
#include <windows.h>
#include <math.h>


void draw_origin()
{
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES);

	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	glEnd();
}

void draw_polygon()
{

	glBegin(GL_QUADS);

	glNormal3f(0.0F, 0.0F, 1.0F);
	glVertex3f(3.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 3.0f, 0.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);

	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

	draw_origin();
	glColor3f(0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	draw_polygon();
	glPushMatrix();

	//
	glColor3f(0.0, 0.8, 0.6);
	glTranslated(3.0, 1.0, 0.0); //Move back.
	//glScalef(1.0, 1.5, 1.0);
	glRotatef(120, 0, 0, 1);         //Rotate operation
	glTranslated(-3.0, -1.0, 0.0); //Move to the original point (0,0).
	draw_polygon();

	glPopMatrix();

	glFlush();                    //Force the processor to draw immediately
}

void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  //Set the clear color to black

	// Specify the domain of the viewing window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// The para are: (left, right, bottom, top)
	gluOrtho2D(-8.0, 8.0, -8.0, 8.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[])
{
	// Initialize GLUT function callings
	glutInit(&argc, (char**)argv);

	// Set window size (width, height) in number of pixels  	
	glutInitWindowSize(600, 600);

	// Specify window position, from the left and top of the screen, in numbers of pixels 
	glutInitWindowPosition(200, 100);

	// Specify a window creation event 
	glutCreateWindow("A Yellow Quad.");

	//Specify the drawing function, called when the window is created or re-drew 
	glutDisplayFunc(display);

	myinit();		      //Invoke this function for initializaton	

	glutMainLoop();       // Enter the event processing loop

	return 0;
}
