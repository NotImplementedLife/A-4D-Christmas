#pragma once

#include <gba.h>

class Enemy
{
private:
	u8 actual_r;
public:
	u16 x, y, dx, dy;
	u8 r;
	float dT,dP;
	float T,P;
	Enemy(u8 _r=10, u16 _dx=0, u16 _dy=0);	
	void update();
	void draw();	
};