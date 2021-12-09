#pragma once

#include <gba.h>
#include "scene.hpp"

class CreditsScene : public Scene
{
private:
	
public:
	CreditsScene();
	Scene* (*run())(void);
	~CreditsScene();
};
