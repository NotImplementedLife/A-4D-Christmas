#include "topbar.hpp"

#include <gba.h>
#include "vbuffer.hpp"
#include "top-bar.h"

namespace nTopbar
{
	
	const u16 cl_heart = 0x001F;
	const u16 cl_disabled = 0x1825;
	
	const u16 cl_inactive_border = 0x1404;
	
	const u16 cl_progress_bg = 0x673F;
	const u16 cl_progress_fill = 0x01BF;
	
	
	// color indices
	static u8 ci_heart0;
	static u8 ci_heart1;
	static u8 ci_heart2;
	static u8 ci_progress_border;
	static u8 ci_progress_fill;
	static u8 ci_progress_bg;
	static u8 ci_L;		
	
	
	
	
	void init()
	{
		dmaCopy((void*)top_barBitmap,(void*)vBuffer::WMEM,top_barBitmapLen);
		for(int i=0;i<top_barBitmapLen;i++)
			vBuffer::WMEM[i]|=0x8080;
		dmaCopy((void*)top_barPal,(void*)(BG_PALETTE+128),top_barPalLen);
		
		u16* pal = BG_PALETTE+128;
		for(u8 i=0;i<16;i++,pal++)
		{
			if(*pal==0x13E0) ci_heart0 = 128+i;
			else if(*pal==0x001F) ci_heart1 = 128+i;
			else if(*pal==0x31DF) ci_heart2 = 128+i;			
			else if(*pal==0x6BE0) ci_progress_border = 128+i;		
			else if(*pal==0x01BF) ci_progress_fill = 128+i;
			else if(*pal==0x673F) ci_progress_bg = 128+i;
			else if(*pal==0x33F) ci_L = 128+i;
		}
		
		BG_PALETTE[ci_progress_border] = cl_inactive_border;
		BG_PALETTE[ci_progress_bg] = cl_progress_bg;
		BG_PALETTE[ci_progress_fill] = cl_progress_fill;
		
		BG_PALETTE[ci_heart0] = 
		BG_PALETTE[ci_heart1] = cl_heart;
		BG_PALETTE[ci_heart2] = cl_disabled;
	}
}