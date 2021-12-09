#include "main_scene.hpp"

#include <gba.h>

#include <stdlib.h>

#include "vbuffer.hpp"
#include "sphere.hpp"
#include "enemy.hpp"
#include "utils.hpp"

#include "sleigh.hpp"
#include "topbar.hpp"
#include "title_scene.hpp"

#include "game-over.h"

static u8 gameover_img[game_overBitmapLen];

MainScene::MainScene()
{	
	vBuffer::clear();
	dmaCopy(game_overBitmap,gameover_img,game_overBitmapLen);	
	for(int i=0;i<game_overBitmapLen;i++)
		if(gameover_img[i]) gameover_img[i]+=192;
	
	SetMode(MODE_4 | BG2_ON | OBJ_ENABLE | OBJ_1D_MAP);	
	for(u16 i=0;i<32;i++)
	{
		u8 r=4, g=0, b=5;		
		((u16*)BG_PALETTE)[i]=RGB5(min(31,i+r),min(31,i+g),min(31,i+b));		
	}		
	dmaCopy((void*)(nSphere::sphere_colors+1),BG_PALETTE+2,30);
	
	((u16*)BG_PALETTE)[32]=RGB5(31,31,14);		
	nTopbar::init();
	VBlankIntrWait();
	nSleigh::init();	
	nSleigh::show();
	nSleigh::update();
	dmaCopy(game_overPal,BG_PALETTE+192,game_overPalLen);	
}

void MainScene::input_handler(bool update_sleigh)
{
	scanKeys();
	u16 keys_down = keysDown();
	u16 keys_held = keysHeld();
	u16 keys_up = keysUp();	
	
	if(keys_down & KEY_A) laser=true;	
	
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
	laser = false;
	for(int i=0;i<5;i++)
	{
		if(enemies[i]!=NULL)
		{
			s16 score = (s16)nTopbar::get_score()-100;
			enemies[i]->update();
			for(u8 i=0;i<3 && score>0;i++,score-=100) enemies[i]->update();			
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
		//VBlankIntrWait();		
	}	
	if(laser)
		vBuffer::draw_line(nSleigh::x+16,nSleigh::y+16,120,50,32);
	for(int j=0;j<5;j++)
	{
		if(!cooldown && enemies[j]!=NULL)
		{
			u16 ex = enemies[j]->x>>8;
			u16 ey = enemies[j]->y>>8;
			if(ey>=nSleigh::y+16)
			{
				u16 xx = abs(nSleigh::x+16-ex);
				u16 yy = ey - nSleigh::y-16;
				u16 rr = enemies[j]->actual_r+2;
				if(xx*xx+yy*yy<=rr*rr)
				{
					// sleigh shot					
					if(!nTopbar::take_a_heart())
					{
						game_over=true;
						nTopbar::save_score_if_high();
						return;
					}
					cooldown=32;
				}
			}
			if(laser)
			{
				u8 shooted = 0;
				u8* pts = vBuffer::points;				
				for(int k=0;k<vBuffer::points_count;k++)
				{
					u8 x = *(pts++);
					u8 y = *(pts++);
					if(y>100)
					{
						u16 xx = abs(x-ex);
						u16 yy = abs(y-ey);
						u16 rr = enemies[j]->actual_r+2;
						if(xx*xx+yy*yy<=rr*rr)
						{
							// shoot enemy
							nTopbar::inc_shot_enemies();
							shooted++;
							delete enemies[j];
							enemies[j]=NULL;
						}
					}
				}
				if(shooted>0)
				{
					nTopbar::add_to_score(1<<(shooted-1));
				}
			}
		}
	}	
	if(cooldown)
	{
		u8 q = cooldown & 7;
		if(q<4)
			nSleigh::show(); 
		else
			nSleigh::hide();
		cooldown--;
	}
}

Scene* (*MainScene::run())(void)
{				
	if(!game_over)
	{
		vBuffer::clear(0,42);
		update_enemies();
	}
	else
	{
		for(int y=0;y<10;y++)
			for(int x=0;x<64;x++)
			{
				if(gameover_img[64*y+x])
					vBuffer::WMEM[88+x+240*(75+y)]=gameover_img[64*y+x];
			}
		VBlankIntrWait();
		vBuffer::draw();
		scanKeys();				
		return keysDown() ? next_TitleScene : NULL;
	}
	
	input_handler(true);
	
	VBlankIntrWait();
	vBuffer::draw();
	
	nSleigh::update();
	return NULL;
}


MainScene::~MainScene()
{				
	nSleigh::hide();
	nSleigh::update();	
	for(u8 i=0;i<5;i++)
		if(enemies[i]!=NULL)
		{
			delete enemies[i];
			enemies[i]=NULL;
		}
	delete[] enemies;	
}



