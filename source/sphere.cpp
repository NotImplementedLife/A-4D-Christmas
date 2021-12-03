#include "sphere.hpp"
#include <gba_systemcalls.h>
#include <math.h>

#include "vbuffer.hpp"
#include "utils.hpp"
#include <stdio.h>

#include <gba.h>
namespace nSphere
{	
	u8 crt_points[3*points_count];

	const float raw_points[3*points_count] = 
	{
		+0.000000, -1.000000, +0.000000,
		-0.345491, -0.809017, +0.475528,
		-0.559017, -0.809017, +0.181636,
		-0.559017, -0.809017, -0.181636,
		-0.345491, -0.809017, -0.475528,
		+0.000000, -0.809017, -0.587785,
		+0.345492, -0.809017, -0.475528,
		+0.559017, -0.809017, -0.181636,
		+0.559017, -0.809017, +0.181636,
		+0.345492, -0.809017, +0.475528,
		+0.000000, -0.809017, +0.587785,
		-0.559017, -0.309017, +0.769421,
		-0.904508, -0.309017, +0.293893,
		-0.904508, -0.309017, -0.293893,
		-0.559017, -0.309017, -0.769421,
		+0.000000, -0.309017, -0.951057,
		+0.559017, -0.309017, -0.769421,
		+0.904509, -0.309017, -0.293893,
		+0.904509, -0.309017, +0.293893,
		+0.559017, -0.309017, +0.769421,
		+0.000000, -0.309017, +0.951057,
		-0.559017, +0.309017, +0.769421,
		-0.904509, +0.309017, +0.293893,
		-0.904509, +0.309017, -0.293893,
		-0.559017, +0.309017, -0.769421,
		+0.000000, +0.309017, -0.951057,
		+0.559017, +0.309017, -0.769421,
		+0.904509, +0.309017, -0.293893,
		+0.904509, +0.309017, +0.293893,
		+0.559017, +0.309017, +0.769421,
		+0.000000, +0.309017, +0.951057,
		-0.345492, +0.809017, +0.475528,
		-0.559017, +0.809017, +0.181636,
		-0.559017, +0.809017, -0.181636,
		-0.345492, +0.809017, -0.475528,
		+0.000000, +0.809017, -0.587785,
		+0.345492, +0.809017, -0.475528,
		+0.559017, +0.809017, -0.181636,
		+0.559017, +0.809017, +0.181636,
		+0.345492, +0.809017, +0.475528,
		+0.000000, +0.809017, +0.587785,
		+0.000000, +1.000000, +0.000000
	};
	
	bool visible_points[points_count];
	
	const int triangles_count=80;
	
	struct Triangle
	{
		u16 pid1, pid2, pid3;
		bool draw1=1, draw2=1, draw3=1;
	} triangles[] = 
	{ 
		{  0,  1,  2 },
		{  0,  2,  3 },
		{  0,  3,  4 },
		{  0,  4,  5 },
		{  0,  5,  6 },
		{  0,  6,  7 }, 
		{  0,  7,  8 }, 
		{  0,  8,  9 },
		{  0,  9, 10 },
		{  0, 10, 1 },
		
		{  1,  2, 11, 0, 0, 1}, {  2,  11, 12, 0, 1, 1},
		{  2,  3, 12, 0, 0, 1}, {  3,  12, 13, 0, 1, 1},
		{  3,  4, 13, 0, 0, 1}, {  4,  13, 14, 0, 1, 1},
		{  4,  5, 14, 0, 0, 1}, {  5,  14, 15, 0, 1, 1},
		{  5,  6, 15, 0, 0, 1}, {  6,  15, 16, 0, 1, 1},
		{  6,  7, 16, 0, 0, 1}, {  7,  16, 17, 0, 1, 1},
		{  7,  8, 17, 0, 0, 1}, {  8,  17, 18, 0, 1, 1},
		{  8,  9, 18, 0, 0, 1}, {  9,  18, 19, 0, 1, 1},
		{  9, 10, 19, 0, 0, 1}, { 10,  19, 20, 0, 1, 1},
		{ 10,  1, 20, 0, 0, 1}, {  1,  20, 11, 0, 1, 1},
		
		{ 11, 12, 21, 0, 0, 1}, { 12,  21, 22, 0, 1, 1},
		{ 12, 13, 22, 0, 0, 1}, { 13,  22, 23, 0, 1, 1},
		{ 13, 14, 23, 0, 0, 1}, { 14,  23, 24, 0, 1, 1},
		{ 14, 15, 24, 0, 0, 1}, { 15,  24, 25, 0, 1, 1},
		{ 15, 16, 25, 0, 0, 1}, { 16,  25, 26, 0, 1, 1},
		{ 16, 17, 26, 0, 0, 1}, { 17,  26, 27, 0, 1, 1},
		{ 17, 18, 27, 0, 0, 1}, { 18,  27, 28, 0, 1, 1},
		{ 18, 19, 28, 0, 0, 1}, { 19,  28, 29, 0, 1, 1},
		{ 19, 20, 29, 0, 0, 1}, { 20,  29, 30, 0, 1, 1},
		{ 20, 11, 30, 0, 0, 1}, { 11,  30, 21, 0, 1, 1},
		
		{ 21, 22, 31, 0, 0, 1}, { 22,  31, 32, 0, 1, 1},
		{ 22, 23, 32, 0, 0, 1}, { 23,  32, 33, 0, 1, 1},
		{ 23, 24, 33, 0, 0, 1}, { 24,  33, 34, 0, 1, 1},
		{ 24, 25, 34, 0, 0, 1}, { 25,  34, 35, 0, 1, 1},
		{ 25, 26, 35, 0, 0, 1}, { 26,  35, 36, 0, 1, 1},
		{ 26, 27, 36, 0, 0, 1}, { 27,  36, 37, 0, 1, 1},
		{ 27, 28, 37, 0, 0, 1}, { 28,  37, 38, 0, 1, 1},
		{ 28, 29, 38, 0, 0, 1}, { 29,  38, 39, 0, 1, 1},
		{ 29, 30, 39, 0, 0, 1}, { 30,  39, 40, 0, 1, 1},
		{ 30, 21, 40, 0, 0, 1}, { 21,  40, 31, 0, 1, 1},
		
		{ 41, 31, 32 },
		{ 41, 32, 33 },
		{ 41, 33, 34 },
		{ 41, 34, 35 },
		{ 41, 35, 36 },
		{ 41, 36, 37 }, 
		{ 41, 37, 38 }, 
		{ 41, 38, 39 },
		{ 41, 39, 40 },
		{ 41, 40, 31 },
	};
	
	bool triangle_is_visible(Triangle t)
	{
		return visible_points[t.pid1] && visible_points[t.pid2] && visible_points[t.pid3];
	}
	
	void triangle_draw(Triangle t)
	{		
		if(!triangle_is_visible(t)) return;
		u8 x1 = crt_points[3*t.pid1], y1 = crt_points[3*t.pid1+1], z1 = crt_points[3*t.pid1+2];
		u8 x2 = crt_points[3*t.pid2], y2 = crt_points[3*t.pid2+1], z2 = crt_points[3*t.pid2+2];
		u8 x3 = crt_points[3*t.pid3], y3 = crt_points[3*t.pid3+1], z3 = crt_points[3*t.pid3+2];
		if(t.draw1) vBuffer::draw_line(x1,y1,x2,y2,min(z1,z2));
		if(t.draw2) vBuffer::draw_line(x2,y2,x3,y3,min(z2,z3));
		if(t.draw3) vBuffer::draw_line(x3,y3,x1,y1,min(z3,z1));
	}		
	
	
	void make_sphere(float rotX,float rotY,int scale, int center_x,int center_y)
	{		
		float sinX = sin(rotX), cosX = cos(rotX);
		float sinY = sin(rotY), cosY = cos(rotY);
				
		const float* src = raw_points;
		u8* dest = crt_points;
		
		for(u8 i=0;i<points_count;i++)
		{			
			float x=*(src++);			
			float y=*(src++);			
			float z=*(src++);			
		
			// rotate 3d point
			float x1 = x*cosY + z*sinY;
			float y1 = y;
			float z1 = -x*sinY + z*cosY;
			
			x = x1;
			y = y1*cosX - z1*sinX;
			z = y1*sinX + z1*cosX;
				
			int ix=center_x+(int)(x*scale);
			int iy=center_y+(int)(y*scale);
			int iz=(int)(z*16);
			
			*(dest++) = ix;
			*(dest++) = iy;		
			*(dest++) = 15+iz;

			visible_points[i] = (0<=ix && 0<=iy && ix<240 && iy<160 && iz>=-7);
		}
		
		for(int i=0;i<triangles_count;i++)
			triangle_draw(triangles[i]);		
	}
	
	
}




