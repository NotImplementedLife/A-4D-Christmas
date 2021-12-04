#include "enemy.hpp"

#include <stdlib.h>
#include "sphere.hpp"

Enemy::Enemy(u8 _r, u16 _dx, u16 _dy)
{		
	x=120, y=80;			
	T=P=0;	
	dT = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dP = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r=_r; 
	dx = _dx;
	dy = _dy;
}

void Enemy::update()
{
	T+=dT;
	P+=dP;
	x+=dx;
	y+=dy;
}

void Enemy::draw()
{
	nSphere::make_sphere(T, P, r, x>>8, y>>8);
}