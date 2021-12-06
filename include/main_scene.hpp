#pragma once

#include "enemy.hpp"

class MainScene
{
private:
	Enemy* enemies[5] = {NULL, NULL, NULL, NULL, NULL};
	bool laser = false;
public:
	MainScene();
	
	void update_enemies();
	
	void input_handler(bool update_sleigh);
	
	void run();	
	
	int k=0;
};

