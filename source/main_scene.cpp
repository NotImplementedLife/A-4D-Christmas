#include "main_scene.hpp"

#include <gba.h>

#include <stdlib.h>

#include "vbuffer.hpp"
#include "sphere.hpp"
#include "enemy.hpp"

MainScene::MainScene()
{
	SetMode(MODE_4 | BG2_ON);
	for(u16 i=0;i<256;i++)
	{
		((u16*)BG_PALETTE)[i]=RGB5(i%32,i%32,i%32);
	}	
	for(u8 y=0;y<160;y++)
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
	vBuffer::draw();	
}

Enemy e(20,-0x0080,0x0080);

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
			//bool left =  enemies[i]->x>(240<<8) && (((enemies[i]->x+((enemies[i]->r/2)<<8)))&0x8000);
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
	nSphere::make_sphere(k*0.2,k*0.2, 1,120, 100);
	nSphere::make_sphere(k*0.2,k*0.2, 20,60);
	nSphere::make_sphere(k*0.1,k*0.1, 20,180);	
	nSphere::make_sphere(k*0.1,k*0.1, 10,120);	
	nSphere::make_sphere(k*0.1,k*0.1, 15,5,150);	
	//nSphere::make_sphere(0,0);	
	VBlankIntrWait();
	vBuffer::draw();
	k++;
}




