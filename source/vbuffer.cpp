#include "vbuffer.hpp"

#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_input.h>
#include <string.h>
#include <math.h>

#include <gba_dma.h>
#include "dma.hpp"


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
	
	u8 points[256];
	u16 points_count;
	
	void draw_line(s16 x0,s16 y0,s16 x1,s16 y1,u8 color)
	{				
		nRaster::bresenham(points_count,points,x0,y0,x1,y1);
		draw_points(points_count,points,color);
	}
	
	static const u16 mul_table_240[161] = 
	{
		  0 * 240,   1*240,   2*240,   3*240,   4*240,   5*240,   6*240,   7*240,   8*240,   9*240, 
		 10 * 240,  11*240,  12*240,  13*240,  14*240,  15*240,  16*240,  17*240,  18*240,  19*240, 
		 20 * 240,  21*240,  22*240,  23*240,  24*240,  25*240,  26*240,  27*240,  28*240,  29*240, 
		 30 * 240,  31*240,  32*240,  33*240,  34*240,  35*240,  36*240,  37*240,  38*240,  39*240, 
		 40 * 240,  41*240,  42*240,  43*240,  44*240,  45*240,  46*240,  47*240,  48*240,  49*240,
		 50 * 240,  51*240,  52*240,  53*240,  54*240,  55*240,  56*240,  57*240,  58*240,  59*240,
		 60 * 240,  61*240,  62*240,  63*240,  64*240,  65*240,  66*240,  67*240,  68*240,  69*240, 
		 70 * 240,  71*240,  72*240,  73*240,  74*240,  75*240,  76*240,  77*240,  78*240,  79*240, 
		 80 * 240,  81*240,  82*240,  83*240,  84*240,  85*240,  86*240,  87*240,  88*240,  89*240, 
		 90 * 240,  91*240,  92*240,  93*240,  94*240,  95*240,  96*240,  97*240,  98*240,  99*240, 
		100 * 240, 101*240, 102*240, 103*240, 104*240, 105*240, 106*240, 107*240, 108*240, 109*240, 
		110 * 240, 111*240, 112*240, 113*240, 114*240, 115*240, 116*240, 117*240, 118*240, 119*240, 
		120 * 240, 121*240, 122*240, 123*240, 124*240, 125*240, 126*240, 127*240, 128*240, 129*240, 
		130 * 240, 131*240, 132*240, 133*240, 134*240, 135*240, 136*240, 137*240, 138*240, 139*240, 
		140 * 240, 141*240, 142*240, 143*240, 144*240, 145*240, 146*240, 147*240, 148*240, 149*240, 
		150 * 240, 151*240, 152*240, 153*240, 154*240, 155*240, 156*240, 157*240, 158*240, 159*240, 160*240,
	};
	
	void clear(u8 color, u8 line0, u8 line1)
	{
		dmaFillDouble(WMEM+mul_table_240[line0],color|(color<<8)|(color<<16)|(color<<24),mul_table_240[line1-line0]);
	}
	
	
}