#include "enemy.hpp"

#include <stdlib.h>
#include "sphere.hpp"

Enemy::Enemy(int _r)
{		
	x=120, y=80;		
	r=_r;
	T=P=0;
	dT = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dP = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Enemy::draw()
{
	nSphere::make_sphere(T,P, r, x,y);
}