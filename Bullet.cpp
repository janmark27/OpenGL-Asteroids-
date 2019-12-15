#include "Bullet.h"
#include <vector>

using namespace std;

Bullet::Bullet(GLfloat playerAngle)
{
	bulletAngle = playerAngle + 90; // takes the angle the player had the moment it was shot 
	bulletxTip = 0.0;
	bulletyTip = 0.0;
	bulletRadius = 0.2f; // radius to be used for collision detection
}

void Bullet::updateBullet(vector<Asteroid>& _Asteroids, GLfloat& score) 
{
	bulletxTip += cos((M_PI / 180) * bulletAngle) * 0.01; //updates the coordinate of the bullet 
	bulletyTip += sin((M_PI / 180) * bulletAngle) * 0.01;
	collision(_Asteroids, score); //checks for collisions
}

void Bullet::drawBullet() 
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(bulletxTip + bulletRadius * cos((M_PI / 180) * bulletAngle)        , bulletyTip + bulletRadius * sin((M_PI / 180) * bulletAngle));			//Using the bulets angle and Pythagora's Theorem the bullet 
	glVertex2f(bulletxTip + bulletRadius * cos((M_PI / 180) * (bulletAngle + 120)), bulletyTip + bulletRadius * sin((M_PI / 180) * (bulletAngle + 120))); // we can calculate the path the bullet is supposed to go
	glVertex2f(bulletxTip + bulletRadius * cos((M_PI / 180) * (bulletAngle + 240)), bulletyTip + bulletRadius * sin((M_PI / 180) * (bulletAngle + 240)));
	
	glEnd();
}
void Bullet::collision(vector<Asteroid>& _Asteroids, GLfloat& score)
{
	for (int i = 0; i < _Asteroids.size(); i++)
	{
		if (sqrt(pow(_Asteroids[i].asteroidxPos - bulletxTip, 2) + pow(_Asteroids[i].asteroidyPos - bulletyTip, 2 ))< _Asteroids[i].asteroidRadius + bulletRadius) // Calculating if the distance between the bullet and asteroid is less than the sum of their radiuses
		{
			_Asteroids.erase(_Asteroids.begin() + i); // if there is a collision the element of the vector of the destroyed asteroid will be erased 
			score += 10.0; // and you get 10 points for that!
		}
	}
}
Bullet::~Bullet(){}