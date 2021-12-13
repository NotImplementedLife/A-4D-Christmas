#include "tutorial_scene.hpp"
#include <stdio.h>
#include "topbar.hpp"
#include "title_scene.hpp"

TutorialScene::TutorialScene()
{
	consoleDemoInit();	
	BG_PALETTE[0]=RGB5(4,0,5);	
	iprintf("\033[%d;%dHTutorial\n\n", 1, 11);
	iprintf("   Left/Right - Move sleigh\n");
	iprintf("   A          - Shoot\n");
	iprintf("   L          - Combo\n");
	
	
}

Scene* (*TutorialScene::run())(void)
{	
	VBlankIntrWait();
	scanKeys();	
	return keysDown() ? next_TitleScene : NULL;
}

TutorialScene::~TutorialScene() {}