#pragma once

class Enemy
{
public:
	int x, y, r;
	float dT,dP;
	float T,P;
	Enemy(int _r=10);
	void draw();
};