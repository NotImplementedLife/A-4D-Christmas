#include "sleigh.hpp"

#include <gba.h>
#include "sleigh-sprite.h"

namespace nSleigh
{
	//https://github.com/JeffRuLz/Celeste-Classic-GBA/blob/master/src/pico8.c#L149
	static OBJATTR obj_buffer[128] = { 0 };
	
	void spr(u16 n, s16 x, s16 y, u8 layer=0)
	{
		OBJATTR* obj = &(obj_buffer[0]);
		obj->attr0 = OBJ_Y(y) | ATTR0_COLOR_256 | ATTR0_SQUARE;
		obj->attr1 = OBJ_X(x) | ATTR1_SIZE_32;
		obj->attr2 = OBJ_CHAR(n) | OBJ_PRIORITY(layer) | OBJ_SQUARE;
		obj->attr2 |= ATTR2_PALETTE(0);
	}
	
	void updateOAM()
	{
		//upload OAM copy to real OAM
		CpuFastSet(obj_buffer, OAM, ((sizeof(OBJATTR))/4) | COPY32);
		obj_buffer[0].attr0 = OBJ_DISABLE;
	}
	
	u8 x = 104;
	u16 tile_number = 512;
	u8 scr_y = y;
	
	void hide()
	{
		scr_y = 160;		
	}
	
	void show() 
	{ 
		scr_y = y;	
	}
	
	
	void set_tiles(u16 sprite_X)
	{
		tile_number=sprite_X;
	}
	
	void move(u16 dx)
	{
		if(dx==0) return;
		if(dx & 0x8000)
			nSleigh::set_tiles(nSleigh::sprite_L);
		else
			nSleigh::set_tiles(nSleigh::sprite_R);
		u16 xx=x+dx;
		if(0<=xx && xx<208) x=xx;
	}
	
	void update()
	{
		spr(tile_number,x,scr_y);
		updateOAM();
	}
	
	void init()
	{
		dmaCopy((void*)sleigh_spriteTiles,(void*)0x06014000,sleigh_spriteTilesLen);	
		dmaCopy((void*)sleigh_spritePal,SPRITE_PALETTE,512);
		CpuFastSet(obj_buffer, OAM, ((sizeof(OBJATTR))/4)*128 | COPY32);
		spr(sprite_0,104,124,0);
		updateOAM();		
	}
}