#pragma once
#include "..\include\freeglut.h"
#include <math.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#define M_PI 3.14159265358979323846 

class Asteroid
{
public:

	GLfloat asteroidxPos, asteroidyPos, asteroidRadius = 0.0f, r, g, b, s, theta, rotation = 0.0;

	Asteroid(GLfloat _x, GLfloat _y);
	~Asteroid();
	void drawAsteroid();	
};