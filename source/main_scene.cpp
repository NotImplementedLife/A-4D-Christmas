#include "main_scene.hpp"

#include <gba.h>

#include <stdlib.h>

#include "vbuffer.hpp"
#include "sphere.hpp"
#include "enemy.hpp"
#include "utils.hpp"

#include "sleigh-sprite.h"

MainScene::MainScene()
{
	SetMode(MODE_4 | BG2_ON);
	for(u16 i=0;i<256;i++)
	{
		u8 r=2, g=0, b=3, a=10;		
		((u16*)BG_PALETTE)[i]=RGB5(min(31,i+r),min(31,i+g),min(31,i+b));
		
	}	
	/*for(u8 y=0;y<160;y++)
	{
		for(u8 x=0;x<240;x++)
			vBuffer::WMEM[240*y+x]=y;			
	}			
	VBlankIntrWait();
	vBuffer::draw();	
	for(u8 y=0;y<160;y++)
	{
		for(u8 x=0;x<240;x++)
			vBuffer::WMEM[240*y+x]=x;			
	}		
	vBuffer::draw();*/
	VBlankIntrWait();
	dmaCopy((void*)sleigh_spriteTiles,(void*)0x06013800,sleigh_spriteTilesLen);	
	dmaCopy((void*)sleigh_spritePal,SPRITE_PALETTE,512);	
}

void MainScene::update_enemies()
{
	for(int i=0;i<5;i++)
	{
		if(enemies[i]!=NULL)
		{
			enemies[i]->update();
			//enemies[i]->update();
			//enemies[i]->update();
			//enemies[i]->update();			
			enemies[i]->draw();				
			if(enemies[i]->y>=(160+enemies[i]->r/2)<<8)
			{
				delete enemies[i];
				enemies[i]=NULL;
			}
		}
		else
		{
			u8 sgn = rand()%2;
			u16 dx = 30 + rand()%80;
			if(sgn) dx=-dx;
			u16 dy = 100+rand()%200;
			enemies[i]=new Enemy(10+rand()%10, dx, dy);
		}
	}
}

void MainScene::run()
{	
	vBuffer::clear(2);
			
	update_enemies();
	VBlankIntrWait();
	vBuffer::draw();
	
	return;
	
	//vBuffer::draw_line(120,82,73,80);
	float k1 = k*0.1;
	float k2 = k*0.2;	
	nSphere::make_sphere(k2,k2, 1,120, 100);
	nSphere::make_sphere(k2,k2, 20,60);
	nSphere::make_sphere(k1,k1, 20,180);
	nSphere::make_sphere(k1,k1, 10,120);	
	nSphere::make_sphere(k1,k1, 15,5,150);	
	//nSphere::make_sphere(0,0);	
	VBlankIntrWait();
	vBuffer::draw();
	k++;
}




