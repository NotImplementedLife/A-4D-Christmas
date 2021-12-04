#include "main_scene.hpp"

#include <gba.h>

#include <stdlib.h>

#include "vbuffer.hpp"
#include "sphere.hpp"
#include "enemy.hpp"
#include "utils.hpp"

#include "sleigh.hpp"

MainScene::MainScene()
{
	SetMode(MODE_4 | BG2_ON | OBJ_ENABLE | OBJ_1D_MAP);
	for(u16 i=0;i<256;i++)
	{
		u8 r=4, g=0, b=5;		
		((u16*)BG_PALETTE)[i]=RGB5(min(31,i+r),min(31,i+g),min(31,i+b));
		
	}		
	VBlankIntrWait();
	nSleigh::init();
}

void MainScene::input_handler()
{
	scanKeys();
	u16 keys_down = keysDown();
	u16 keys_held = keysHeld();
	u16 keys_up = keysUp();	
	
	if((keys_up & (KEY_LEFT))|(keys_up & (KEY_RIGHT)))
		nSleigh::set_tiles(nSleigh::sprite_0);
		
	
	if(keys_held & KEY_LEFT)
		nSleigh::move(-1);
	else if(keys_held & KEY_RIGHT)
		nSleigh::move(1);
		
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
		input_handler();
	}
}

void MainScene::run()
{	
	vBuffer::clear(0);
			
	update_enemies();
		
	input_handler();
	
	VBlankIntrWait();
	vBuffer::draw();
	
	nSleigh::update();
	
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




