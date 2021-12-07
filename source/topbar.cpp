#include "topbar.hpp"

#include "vbuffer.hpp"
#include "top-bar.h"
#include "digits.h"

namespace nTopbar
{
	// 10 * (8x8), effective (5x8) images 0..9
	static u8 digits_glyph[640];
	
	const u16 cl_heart = 0x001F;
	const u16 cl_disabled = 0x1825;
	
	const u16 cl_inactive_border = 0x1404;
	
	const u16 cl_progress_bg = 0x673F;
	const u16 cl_progress_fill = 0x01BF;
	
	
	// color indices
	static u8 ci_heart[3];	
	static u8 ci_progress_border;
	static u8 ci_progress_fill;
	static u8 ci_progress_bg;
	static u8 ci_L;
	
	
	static u8 hearts_cnt;
	static u16 score = 0;
	static u16 highs = 0;
	
	void fill_hearts()
	{
		hearts_cnt = 3;
		BG_PALETTE[ci_heart[0]] = BG_PALETTE[ci_heart[1]] = BG_PALETTE[ci_heart[2]] = cl_heart;
	}
	
	u8 take_a_heart()
	{
		if(hearts_cnt==0) return -1;
		BG_PALETTE[ci_heart[--hearts_cnt]] = cl_disabled;
		return hearts_cnt;
	}
	
	void draw_digit(u8 d, u8 x, u8 y)
	{
		u8* digptr = digits_glyph + 64*d;
		for(u8 q=8;q--;)
		{
			dmaCopy(digptr,vBuffer::WMEM+240*y+x,8);
			y++;			
			digptr+=8;
		}
	}
	
	
	void draw_score(u16 score,u8 x,u8 y)
	{
		x+=30;
		for(u8 q=5;q--;)
		{
			u8 d = score % 10;
			score/=10;
			draw_digit(d,x,y);
			x-=6;
		}
	}
	
	void add_to_score(u16 ds)
	{
		score+=ds;
		draw_score(score,12,2);
	}
	
	u16 get_score()
	{
		return score;
	}
	
	void init()
	{		
		// digits
		dmaCopy((void*)digitsBitmap,(void*)digits_glyph,digitsBitmapLen);
		for(u16 i=0;i<640;digits_glyph[i++] |= 64);		
		BG_PALETTE[64] = 0x1825;
		BG_PALETTE[65] = 0x2FBF;

		// top bar
		dmaCopy((void*)top_barBitmap,(void*)vBuffer::WMEM,top_barBitmapLen);
		for(int i=0;i<top_barBitmapLen;i++)
			vBuffer::WMEM[i]|=0x8080;
		dmaCopy((void*)top_barPal,(void*)(BG_PALETTE+128),top_barPalLen);
		
		u16* pal = BG_PALETTE+128;
		for(u8 i=0;i<16;i++,pal++)
		{
			if(*pal==0x13E0) ci_heart[0] = 128+i;
			else if(*pal==0x001F) ci_heart[1] = 128+i;
			else if(*pal==0x31DF) ci_heart[2] = 128+i;			
			else if(*pal==0x6BE0) ci_progress_border = 128+i;		
			else if(*pal==0x01BF) ci_progress_fill = 128+i;
			else if(*pal==0x673F) ci_progress_bg = 128+i;
			else if(*pal==0x33F) ci_L = 128+i;
		}
		
		BG_PALETTE[ci_progress_border] = cl_inactive_border;
		BG_PALETTE[ci_progress_bg] = cl_progress_bg;
		BG_PALETTE[ci_progress_fill] = cl_progress_fill;
		
		fill_hearts();
		draw_score(0,12,2);
		draw_score(0,12,20);		
	}
}