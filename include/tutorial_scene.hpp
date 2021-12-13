#pragma once

#include <gba.h>
#include "scene.hpp"

class TutorialScene : public Scene
{
private:
	
public:
	TutorialScene();
	Scene* (*run())(void);
	~TutorialScene();
};
