#pragma once

#include "enemy.hpp"

class MainScene
{
private:
	Enemy* enemies[5] = {NULL, NULL, NULL, NULL, NULL};
public:
	MainScene();
	
	void update_enemies();
	
	void input_handler();
	
	void run();	
	
	int k=0;
};

