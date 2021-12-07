#include <gba.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SRAM.hpp"
#include "main_scene.hpp"
#include "title_scene.hpp"

int main(void) 
{
	srand(time(NULL));
	irqInit();
	irqEnable(IRQ_VBLANK);
	
	//bool ok=nSRAM::check_integrity();
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

