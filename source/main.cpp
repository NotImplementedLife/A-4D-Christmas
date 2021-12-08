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
		nSRAM::read(&highscore,2,0x10);
		nTopbar::set_high_score(highscore);
	}
	else
	{
		u16 highscore = 0;
		nSRAM::write(&highscore,2,0x10);
		nTopbar::set_high_score(highscore);
	}	
	
	//iprintf(ok?"Yes":"No");
		
	//Scene* scene=new MainScene();
	Scene* scene=new TitleScene();
		
	while(1) 
	{				
		auto next = scene->run();
		if(next!=NULL)
		{
			delete scene;
			scene = next;
		}
	}
}

