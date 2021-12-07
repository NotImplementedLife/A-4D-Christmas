#pragma once

#include <gba.h>
#include "scene.hpp"

class TitleScene : public Scene
{
private:
	u32 k = 0;
public:
	TitleScene();
	
	Scene* run();
};