#include "raster.hpp"

namespace nRaster
{
	void bresenham(u16 &n,u8 *points,s16 x0,s16 y0,s16 x1,s16 y1)
	{
		n = 0;
		s16 dx = abs(x1-x0);
		s16 sx = x0<x1 ? 1: -1;
		s16 dy = -abs(y1-y0);
		s16 sy = y0<y1 ? 1: -1;
		s16 err = dx + dy;
		bool k=0;
		while(true)
		{
			k=!k;
			if(x0>=0 && y0>=0 && x1<240 && y1<160 && !k)
			{
				*(points++)=x0, *(points++)=y0;
				n++;
			}
			if(x0==x1 && y0==y1) break;			
			if (2*err>=dy)
				err+=dy, x0+=sx;
			else
				err+=dx, y0+=sy;				
		}
	}
}