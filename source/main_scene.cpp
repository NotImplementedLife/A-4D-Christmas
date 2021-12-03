#include "main_scene.hpp"

#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>

#include "vbuffer.hpp"
#include "sphere.hpp"

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

void MainScene::run()
{	
	for(u8 y=0;y<160;y++)
	{
		for(u8 x=0;x<240;x++)
			//vBuffer::WMEM[240*y+x]=(u8)(y+k);	
		vBuffer::WMEM[240*y+x]=0;
	}		
	
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




