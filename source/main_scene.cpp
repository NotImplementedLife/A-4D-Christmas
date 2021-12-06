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
	//((u16*)BG_PALETTE)[32]=RGB5(28,0,0);
	((u16*)BG_PALETTE)[32]=RGB5(31,31,14);
	((u16*)BG_PALETTE)[34]=RGB5(31,0,0);
	((u16*)BG_PALETTE)[34]=RGB5(28,0,0);
	VBlankIntrWait();
	nSleigh::init();
}

void MainScene::input_handler(bool update_sleigh)
{
	scanKeys();
	u16 keys_down = keysDown();
	u16 keys_held = keysHeld();
	u16 keys_up = keysUp();	
	
	laser = keys_down & KEY_A;	
	
	if((keys_up & (KEY_LEFT)) | (keys_up & (KEY_RIGHT)))
		nSleigh::set_tiles(nSleigh::sprite_0);	
	
	if(!update_sleigh) return;
			
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
		
		input_handler(i==3);
		if(laser)
		{
			vBuffer::draw_line(nSleigh::x+16,nSleigh::y+16,120,50,32);
			for(int j=0;j<5;j++)
			{
				if(enemies[j]!=NULL)
				{
					u8* pts = vBuffer::points;
					for(int k=0;k<vBuffer::points_count;k++)
					{
						u8 x = *(pts++);
						u8 y = *(pts++);
						if(y>100)
						{
							u16 xx = abs(x-(enemies[j]->x>>8));
							u16 yy = abs(y-(enemies[j]->y>>8));
							u16 rr = enemies[i]->actual_r+2;
							if(xx*xx+yy*yy<=rr*rr)
							{
								delete enemies[j];
								enemies[j]=NULL;
							}
						}
					}
				}
			}
		}
		//VBlankIntrWait();
	}	
}

void MainScene::run()
{	
	vBuffer::clear(0);
			
	update_enemies();	
	
	input_handler(true);
	
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




