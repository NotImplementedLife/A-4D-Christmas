#pragma once

#include <gba_systemcalls.h>

namespace nSphere
{	
	const int points_count = 42;
	extern u8 crt_points[3*points_count];
	extern const float raw_points[3*points_count];
	
	void make_sphere(float rotX,float rotY,int scale=80,int center_x=120,int center_y=80);
}

