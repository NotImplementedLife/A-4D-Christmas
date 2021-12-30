#include "tutorial_scene.hpp"
#include <stdio.h>
#include "topbar.hpp"
#include "title_scene.hpp"

u8 hbl_cnt_tut = 0;

__attribute__((target("thumb"))) void text_scene_hblank_handler_tut()
{
	hbl_cnt_tut++;
	hbl_cnt_tut%=8;
	u16 b = (11*(8-hbl_cnt_tut)+31*hbl_cnt_tut)/8;
	u16 g = (27*(8-hbl_cnt_tut)+31*hbl_cnt_tut)/8;
	u16 r = 31;

	BG_PALETTE[241]=RGB5(r,g,b);
}

TutorialScene::TutorialScene()
{
	consoleDemoInit();		
	BG_PALETTE[0]=RGB5(4,0,5);
	BG_PALETTE[241]= RGB5(31,27,11);//0x2FBF; // Yellow Text
	iprintf("\033[%d;%dHTutorial\n\n", 1, 11);
	iprintf("   Left/Right - Move sleigh\n");
	iprintf("   A          - Shoot\n");
	iprintf("   L          - Combo\n");
		
	irqSet(IRQ_HBLANK, text_scene_hblank_handler_tut);
	irqEnable(IRQ_HBLANK);
}

Scene* (*TutorialScene::run())(void)
{	
	VBlankIntrWait();
	hbl_cnt_tut=0;
	scanKeys();	
	return keysDown() ? next_TitleScene : NULL;
}

TutorialScene::~TutorialScene() 
{	
	irqDisable(IRQ_HBLANK);
	irqSet(IRQ_HBLANK,0);
}