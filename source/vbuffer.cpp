#include "vbuffer.hpp"

#include <gba_console.h>
#include <gba_dma.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_input.h>
#include <string.h>
#include <math.h>

#include "utils.hpp"
#include "raster.hpp"

namespace vBuffer
{
	MODE5_LINE* BACK = MODE5_BB;
	//MODE5_LINE* FRONT = MODE5_FB;

	u8 *WMEM = new u8[240*160];
	
	void flip_page()
	{		
		REG_DISPCNT ^= LCD_FRAME_SELECT;
		if (REG_DISPCNT & LCD_FRAME_SELECT)
		{
			BACK = MODE5_FB;
			//FRONT = MODE5_BB;
		}
		else
		{	
			BACK = MODE5_BB;
			//FRONT = MODE5_FB;
		}		
	}		
	
	void draw()
	{
		dmaCopy(WMEM, BACK, 240*160);
		flip_page();
	}		
	
	void draw_points(u16 n,u8* points,u8 color=31)
	{
		for(;n--;)
		{
			u8 x=*(points++);
			u8 y=*(points++);
			WMEM[240*y+x] = color;
		}
	}    
	
	void draw_line(s16 x0,s16 y0,s16 x1,s16 y1,u8 color=31)
	{
		static u8 *points = new u8[256];
		u16 n;
		nRaster::bresenham(n,points,x0,y0,x1,y1);
		draw_points(n,points,color);
	}
}