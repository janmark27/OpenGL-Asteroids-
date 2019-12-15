#include "Asteroid.h"

Asteroid::Asteroid(GLfloat _x, GLfloat _y)
{
	theta = 0;
	asteroidxPos = (rand() % 2400 * 0.01) - 12;
	asteroidyPos = (rand() % 1800 * 0.01) - 9;
	asteroidRadius = ((rand() % 10) + 10) * 0.1;
	r = (0.3 + rand() % 10) * 0.1;
	g = (0.3 + rand() % 10) * 0.1;
	b = (0.3 + rand() % 10) * 0.1;
	s = (5 + rand() % 7);
	asteroidxPos = _x;
	asteroidyPos = _y;

	while (asteroidxPos <= 2 && asteroidxPos >= -2 || asteroidyPos <= 2 && asteroidyPos >= -2)
	{
		asteroidxPos = (rand() % 2400 * 0.01) - 12;
		asteroidyPos = (rand() % 1800 * 0.01) - 9;
	}
}

void Asteroid::drawAsteroid() {
	theta = 0.0f;
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);

	for (int j = 0; j < s; j++)
	{
		glVertex2f(asteroidRadius * cos(theta + rotation) + asteroidxPos, asteroidRadius * sin(theta + rotation) + asteroidyPos);
		theta += (360.0f / s) * (M_PI / 180.0f);
	}
	rotation += 0.001f;
	glEnd();
}

Asteroid::~Asteroid(){}