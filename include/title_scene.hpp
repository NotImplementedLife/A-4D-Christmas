#pragma once

#include <gba.h>
#include "scene.hpp"

class TitleScene : public Scene
{
private:
	u32 k = 0;
	u8 option;
	void set_option(u8 opt);
	void next_option();
	void prev_option();
	bool input_handler();
public:
	TitleScene();
	
	Scene* (*run())(void);
	//Scene* run();
};