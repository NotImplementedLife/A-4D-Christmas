#pragma once

#include <gba.h>
#include "scene.hpp"

class TutorialScene : public Scene
{	
public:
	TutorialScene();
	Scene* (*run())(void);
	~TutorialScene(); 
};
