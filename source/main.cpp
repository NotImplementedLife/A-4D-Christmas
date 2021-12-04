#include <gba.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SRAM.hpp"
#include "main_scene.hpp"

int main(void) 
{
	srand(time(NULL));
	irqInit();
	irqEnable(IRQ_VBLANK);
	
	//bool ok=nSRAM::check_integrity();
	//iprintf(ok?"Yes":"No");
	
	MainScene ms=MainScene();
		
	while (1) 
	{				
		ms.run();
	}
}

