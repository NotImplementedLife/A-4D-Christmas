#include "title_scene.hpp"
#include <stdlib.h>
#include "vbuffer.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "main_scene.hpp"
#include "credits_scene.hpp"

#include "title-screen.h"

static u8 ci_play;
static u8 ci_tutorial;
static u8 ci_credits;

static const u16 cl_unfocused = 0x780F;
static const u16 cl_focused = 0x7FFF;


TitleScene::TitleScene()
{
	SetMode(MODE_4 | BG2_ON | OBJ_ENABLE | OBJ_1D_MAP);
	for(u16 i=0;i<256;i++)
	{
		u8 r=4, g=0, b=5;		
		((u16*)BG_PALETTE)[i]=RGB5(min(31,i+r),min(31,i+g),min(31,i+b));
	}		
	dmaCopy((void*)(title_screenPal),BG_PALETTE+32,title_screenPalLen);
	for(u16 i=0;i<title_screenPalLen/2;i++)
	{
		if(BG_PALETTE[32+i]==0x7C80) ci_play = 32+i;
		else if(BG_PALETTE[32+i]==0x7DE0) ci_tutorial = 32+i;
		else if(BG_PALETTE[32+i]==0x7FC0) ci_credits = 32+i;
	}
	set_option(ci_play);	
	VBlankIntrWait();	
}

void TitleScene::set_option(u8 opt)
{
	option=opt;
	BG_PALETTE[ci_play] = BG_PALETTE[ci_tutorial] = BG_PALETTE[ci_credits] = cl_unfocused;
	if(opt == ci_play || opt==ci_tutorial || opt==ci_credits)
		BG_PALETTE[opt] = cl_focused;
}

void TitleScene::next_option()
{
	if(option==ci_play)
		set_option(ci_tutorial);
	else if(option==ci_tutorial)
		set_option(ci_credits);
	else if(option==ci_credits)
		set_option(ci_play);
	else 
		set_option(ci_play);	
}

void TitleScene::prev_option()
{
	if(option==ci_play)
		set_option(ci_credits);
	else if(option==ci_tutorial)
		set_option(ci_play);
	else if(option==ci_credits)
		set_option(ci_tutorial);
	else 
		set_option(ci_play);
}

bool TitleScene::input_handler()
{
	scanKeys();
	u16 keys_down = keysDown();
	if(keys_down & KEY_UP)
		prev_option();
	else if(keys_down & KEY_DOWN)
		next_option();
	else if(keys_down & (KEY_START | KEY_A))
		return true;
	return false;
}

Scene* (*TitleScene::run())(void)
{
	vBuffer::clear(0);
	float k1 = k*0.1;
	float k2 = k*0.2;	
	nSphere::make_sphere(k1,k2, 60,120, 80);
	if(input_handler())			
	{
		if (option==ci_play) return next_MainScene;
	}
	u8* wmem = vBuffer::WMEM+16*240;
	u8* title = (u8*)title_screenBitmap;
	for(int i=0;i<title_screenBitmapLen;i++)
	{
		if(*title)
		{
			*(wmem) = 32+(*title);
		}
		wmem++, title++;
	}
	if(input_handler())			
	{
		if (option==ci_play) return next_MainScene;
		if (option==ci_credits) return next_CreditsScene;
	}
	VBlankIntrWait();
	vBuffer::draw();	
	k++;
	
	return NULL;
}