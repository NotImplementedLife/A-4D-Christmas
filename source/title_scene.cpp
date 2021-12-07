#include "title_scene.hpp"
#include <stdlib.h>
#include "vbuffer.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "main_scene.hpp"

#include "title-screen.h"

TitleScene::TitleScene()
{
	SetMode(MODE_4 | BG2_ON | OBJ_ENABLE | OBJ_1D_MAP);
	for(u16 i=0;i<256;i++)
	{
		u8 r=4, g=0, b=5;		
		((u16*)BG_PALETTE)[i]=RGB5(min(31,i+r),min(31,i+g),min(31,i+b));
	}		
	dmaCopy((void*)(title_screenPal),BG_PALETTE+32,title_screenPalLen);
	//((u16*)BG_PALETTE)[32]=RGB5(31,31,14);
	VBlankIntrWait();	
}

Scene* TitleScene::run()
{
	vBuffer::clear(0);
	float k1 = k*0.1;
	float k2 = k*0.2;	
	nSphere::make_sphere(k1,k2, 60,120, 80);
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
	VBlankIntrWait();
	vBuffer::draw();	
	k++;
	scanKeys();
	if(keysDown())
		return new MainScene();
	return NULL;
}