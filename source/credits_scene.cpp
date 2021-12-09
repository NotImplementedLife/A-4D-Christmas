#include "credits_scene.hpp"
#include <stdio.h>
#include "topbar.hpp"
#include "title_scene.hpp"

CreditsScene::CreditsScene()
{
	consoleDemoInit();	
	BG_PALETTE[0]=RGB5(4,0,5);	
	iprintf("\033[%d;%dHA 4D Christmas\n", 1, 8);
	iprintf("\033[%d;%dHNotImpLife  2021\n\n", 2, 7);
	
	iprintf(" This is a submission for GBA Winter Jam 21\n");
	iprintf(" Built with devkitARM & libgba\n");
	iprintf(" Some assets come from stock  images over the internet.\n\n");	
	iprintf(" Player stats:\n");
	iprintf("   High score   : %*u\n", 10, nTopbar::get_high_score());
	iprintf("   Shot enemies : %*lu\n", 10, nTopbar::get_shot_enemies());
	
	
}

Scene* (*CreditsScene::run())(void)
{	
	VBlankIntrWait();
	scanKeys();	
	return keysDown() ? next_TitleScene : NULL;
}

CreditsScene::~CreditsScene() {}