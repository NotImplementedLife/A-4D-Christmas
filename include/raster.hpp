#pragma once
#include <gba_systemcalls.h>
#include <math.h>

namespace nRaster
{
	void bresenham(u16 &n,u8 *points,s16 x0,s16 y0,s16 x1,s16 y1);	
};