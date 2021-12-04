#pragma once

#include <gba_systemcalls.h>

#define LCD_FRAME_SELECT (1 << 4)

namespace vBuffer
{		
	extern u8* WMEM;
	void draw();	
	void draw_points(int n,u8* points,u8 color);
	void draw_line(s16 x0,s16 y0,s16 x1,s16 y1,u8 color);	
	void clear(u8 color=0, u8 line0=0, u8 line1=160);
}