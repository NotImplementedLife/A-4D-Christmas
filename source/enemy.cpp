#include "enemy.hpp"

#include <stdlib.h>
#include "sphere.hpp"

Enemy::Enemy(u8 _r, u16 _dx, u16 _dy)
{		
	x=120<<8, y=50<<8;
	T=P=0;	
	dT = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dP = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r=_r; 
	dx = _dx;
	dy = _dy;
}

void Enemy::update()
{
	float factor = (((float)(y>>8))-50)/110;
	T+=dT;
	P+=dP;
	x+=dx;
	y+=dy;
	actual_r = (u8)(r*factor);
}

void Enemy::draw()
{	
	nSphere::make_sphere(T, P, actual_r, x>>8, y>>8);	
}