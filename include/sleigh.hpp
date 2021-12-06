#pragma once

#include <gba.h>

namespace nSleigh
{
	
	static const u16 sprite_0 = 512;
	static const u16 sprite_R = 544;
	static const u16 sprite_L = 576;
	static const u16 sprite_D[8] = 
	{
		576 + 0*32, 576 + 1*32, 576 + 2*32, 576 + 3*32, 576 + 4*32, 576 + 5*32, 576 + 6*32, 576 + 7*32,
	};
	
	extern u8 x;
	const u8 y=124;
	void init();
	void update();
	void set_tiles(u16 sprite_X);
	void move(u16 dx);
}