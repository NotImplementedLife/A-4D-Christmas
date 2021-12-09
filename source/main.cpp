#include <gba.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SRAM.hpp"
#include "main_scene.hpp"
#include "title_scene.hpp"
#include "topbar.hpp"

int main(void) 
{
	srand(time(NULL));
	irqInit();
	irqEnable(IRQ_VBLANK);
	
	if(nSRAM::check_integrity())
	{
		u16 highscore = 0;
		u32 shot = 0;
		nSRAM::read(&highscore,2,0x10);
		nSRAM::read(&shot,4,0x12);
		nTopbar::set_high_score(highscore);
		nTopbar::set_shot_enemies(shot);
	}
	else
	{
		u32 _0 = 0;		
		nSRAM::write(&_0,2,0x10);
		nSRAM::write(&_0,4,0x12);
		nTopbar::set_high_score(0);
		nTopbar::set_shot_enemies(0);
	}	
		
	Scene* scene=new TitleScene();	
	while(1) 
	{				
		auto get_next = scene->run();
		if(get_next!=NULL)
		{
			delete scene;
			scene = get_next();
		}
	}
}

