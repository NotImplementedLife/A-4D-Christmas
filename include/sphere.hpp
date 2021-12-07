#pragma once

#include <gba_systemcalls.h>

namespace nSphere
{	
	static const int points_count = 42;	
	void make_sphere(float rotX,float rotY,int scale=80,int center_x=120,int center_y=80);

	static const u16 sphere_colors[16] =  
	{
		0x0000,0x2FBF,0x1444,0x13E0,0x001F,0x31DF,0x673F,0x01BF,
		0x7473,0x3A64,0x623A,0x6461,0x615F,0x6C6C,0x636F,0xFF00
	};
}

