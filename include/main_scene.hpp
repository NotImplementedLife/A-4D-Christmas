#pragma once

#include <gba.h>
#include "enemy.hpp"

class MainScene
{
private:
	Enemy** enemies = new Enemy*[5] {NULL, NULL, NULL, NULL, NULL};
	bool laser = false;
	u8 cooldown = 0;
public:
	MainScene();
	
	void update_enemies();
	
	void input_handler(bool update_sleigh);
	
	void run();	
	
	~MainScene();
};

