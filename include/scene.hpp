#pragma once

#include <gba.h>

class Scene
{
public:
	virtual Scene* (*run())(void) = 0; //run() = 0;
	virtual ~Scene() //= default;
	{
		u32 _0 = 0;
		CpuFastSet(&_0, BG_PALETTE, 128 | FILL);
		VBlankIntrWait();
	}	
};

Scene* next_TitleScene();
Scene* next_CreditsScene();
Scene* next_MainScene();