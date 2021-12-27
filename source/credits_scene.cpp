#include "credits_scene.hpp"
#include <stdio.h>
#include "topbar.hpp"
#include "title_scene.hpp"

u8 hbl_cnt_crd = 0;

__attribute__((target("thumb"))) void text_scene_hblank_handler_crd()
{
	hbl_cnt_crd++;
	hbl_cnt_crd%=8;
	u16 b = (11*(8-hbl_cnt_crd)+31*hbl_cnt_crd)/8;
	u16 g = (27*(8-hbl_cnt_crd)+31*hbl_cnt_crd)/8;
	u16 r = 31;

	BG_PALETTE[241]=RGB5(r,g,b);
}

CreditsScene::CreditsScene()
{	
	consoleDemoInit();		
	BG_PALETTE[0]=RGB5(4,0,5);	
	BG_PALETTE[241]= RGB5(31,27,11);//0x2FBF; // Yellow Text
	iprintf("\033[%d;%dHA 4D Christmas\n", 1, 8);
	iprintf("\033[%d;%dHNotImpLife  2021\n\n", 2, 7);
	
	iprintf("   This is a submission for\n      GBA Winter Jam '21\n\n");
	iprintf("          Built with\n      devkitARM & libgba\n\n");
	iprintf(" Some assets come from stock   images over the internet.\n\n");	
	iprintf(" Player stats:\n");
	iprintf("   High score   : %*u\n", 10, nTopbar::get_high_score());
	iprintf("   Shot enemies : %*lu\n", 10, nTopbar::get_shot_enemies());	
	
	irqSet(IRQ_HBLANK, text_scene_hblank_handler_crd);
	irqEnable(IRQ_HBLANK);
}

Scene* (*CreditsScene::run())(void)
{	
	VBlankIntrWait();
	hbl_cnt_crd=0;
	scanKeys();	
	return keysDown() ? next_TitleScene : NULL;
}

CreditsScene::~CreditsScene() 
{	
	irqDisable(IRQ_HBLANK);
	irqSet(IRQ_HBLANK,0);
}