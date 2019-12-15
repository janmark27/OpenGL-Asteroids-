#include "include\freeglut.h"	
#include "3DExample1/Asteroid.h"
#include "3DExample1/Bullet.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

GLfloat xTip, yTip, playerAngle = 0.0f, AsteroidRotation = 0.0f, score = 0.0;
bool PatternSwitch = true, gridSwitch = false;
vector<Asteroid> Asteroids; // Vector to save classes iterations of asteroids and bullets
vector<Bullet> Bullets;

void reshape(int width, int height) // avoid 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -3.0, 3.0, -0.0, 0.0); 

	glMatrixMode(GL_MODELVIEW);

	if (height == 0) // avoid division by 0
	   height = 1;

	GLfloat aspect_ratio = GLfloat(width) / GLfloat(height);

	glViewport(0, 0, width, height); // Viewport Dimensions
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset Coordianate System
	
	if (width <= height)  
	    glOrtho(-10.0f, 10, -10.0f / aspect_ratio, 10 / aspect_ratio, -1.0, 1.0);
	else
	    glOrtho(-10.0f * aspect_ratio, 10.0 * aspect_ratio, -10.0f, 10, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void writeBitmapString(void* font, char* string) // Write a bitmap character string 
{
	char* c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void numberScoreString(GLfloat& score) // Transform the Score variable to a string
{
	char buffer[4];
	GLint ret = snprintf(buffer, sizeof buffer, "%f", score);
	glRasterPos2f(-10.7, 9.1);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, buffer); // Writes the current score
}

void drawTriangle(GLfloat length, GLfloat xT, GLfloat yT)
{
	GLfloat x1, y1, x2, y2, x3, y3;

	x1 = xT - length / 20;
	y1 = yT + length;
	x2 = xT + length;
	y2 = yT - length;
	x3 = xT - length;
	y3 = yT - length;

	glBegin(GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);

	glEnd();
}

void drawLine(GLfloat xL, GLfloat yL)
{
	GLfloat x1, y1, x2, y2, x3, y3, x4, y4;

	x1 = xL;
	y1 = yL;
	x2 = xL;
	y2 = -yL;
	x3 = xL;
	y3 = yL;
	x4 = -xL;
	y4 = yL;

	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void drawGrid()
{
	for (int i = -13; i < 14; i++) // Nested for loop to iterate through the entire background
	{
		for (int j = -10; j < 11; j++)
		{
			glColor3f(1.0, 1.0, 1.0);
			drawLine(i, j);
		}
	}
}

void drawPattern()
{
	bool squareColorSwitch = true;
	
	for (int i = -13; i < 14; i++) // Nested for loop to iterate through the entire background
	{
		for (int j = -11; j < 11; j++)
		{
			glColor3f(0.07, 0.13, 0.25);
			drawTriangle(0.49, i, j);
		}
	}
}

void drawShip(GLfloat xTip, GLfloat yTip, GLfloat x, GLfloat y)
{
	GLfloat x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7;

	glColor3f(0.9, 0.8, 0.1);

	xTip = x;
	yTip = y + 0.5;
	x2 = x + 0.5;
	y2 = y - 1.0;
	x3 = x;
	y3 = y - 0.5;
	x4 = x - 0.5;
	y4 = y - 1.0;
	glBegin(GL_POLYGON);
	glVertex2f(xTip, yTip);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);

	glEnd();

	glFlush();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	if (gridSwitch)  // Activate/deactivate the backgrounds if clicked in the pop up menu
	{
		drawGrid();
	}
	if (PatternSwitch)
	{
		drawPattern();
	}
	
	glPushMatrix();
	
	glRotatef(playerAngle, 0.0, 0.0, 1.0); // Rotation applied only to the player
	drawShip(0.0, 0.0, 0.0, 0.0);
	glPopMatrix();

	if (Asteroids.size() == 0) {  // Once the Asteroid vector has lost all its elements, another set of 6 will be made 
		for (int i = 0; i < 6; i++)
		{
			Asteroids.push_back(Asteroid((rand() % 2400 * 0.01) - 12, ((rand() % 1800 * 0.01) - 9)));
		}
	}

	for (Asteroid& a : Asteroids)
	{
		a.drawAsteroid(); //A new asteroid is created in the vector and drawn 
	}
	
	for (Bullet& a : Bullets)
	{
		a.updateBullet(Asteroids,score);     // Updates the bullets position while checking if it has collided with an asteroid
		a.drawBullet();		//A new bullet is created in the vector and drawn 
	}

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-12.7, 9.1);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "SCORE"); 
	numberScoreString(score);

	glutPostRedisplay();
	glutSwapBuffers();
}

void shootBullet()
{
	Bullets.push_back(Bullet(playerAngle));
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	srand(time(NULL)); // to get random varaibles using rand()
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key) { // Receive the input keys from the player
	case 'a':
		playerAngle += 5.7;
		break;
	case 'd':
		playerAngle -= 5.7;
		break;
	case ' ':
		shootBullet();
	}
	glutPostRedisplay();
}

void popUpMenuActions(int option) {

	switch (option) {
	case 1:
		PatternSwitch = !PatternSwitch; //Turn the pattern and grid on and off
		glEnd();
		break;
	case 2:
		gridSwitch = !gridSwitch;
		glEnd();
		break;
	}
}

void PopUpMenu() {

	int popUpMenu;

	popUpMenu = glutCreateMenu(popUpMenuActions); // popUpMenuAction will handle the events
	
	glutAddMenuEntry("Pattern Switch", 1); // Add entries
	glutAddMenuEntry("Grid Switch", 2);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON); // attach the menu to right click

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Coursework 2D");

	init();

	PopUpMenu();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyInput);

	cout << "           GAME CONTROLS" << endl << endl;
	cout << "1>    Press A to rotate to the left" << endl << endl;
	cout << "2>    Press D to rotate to the right" << endl << endl;
	cout << "3>    Press the Spacebar to shoot the asteroids" << endl << endl;
	glutMainLoop();
	return 0;
}