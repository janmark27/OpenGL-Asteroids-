#pragma once
#include "..\include\freeglut.h"
#include <math.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#include "Asteroid.h"

#define M_PI 3.14159265358979323846 

class Bullet
{
public:

	GLfloat  speedBullet = 0.01, bulletAngle, bulletxTip = 0.0, bulletyTip = 0.0, bulletRadius;
	Bullet(GLfloat playerAngle);
	void updateBullet(std::vector<Asteroid>& _Asteroids,GLfloat& score);
	void drawBullet();
	void collision(std::vector<Asteroid>& _Asteroids, GLfloat& score);
	~Bullet();
};