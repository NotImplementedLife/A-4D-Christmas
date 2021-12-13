#pragma once

#include <gba.h>
#include "enemy.hpp"
#include "scene.hpp"

class MainScene : public Scene
{
private:
	Enemy** enemies = new Enemy*[5] {NULL, NULL, NULL, NULL, NULL};
	bool laser = false;
	u8 cooldown = 0;
	bool game_over = false;
	u8 combo_iter = 0;
public:
	MainScene();
	void update_enemies();
	void input_handler(bool update_sleigh);		
	Scene* (*run())(void);
	~MainScene();
};

