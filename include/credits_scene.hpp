#pragma once

#include <gba.h>
#include "scene.hpp"

class CreditsScene : public Scene
{
public:
	CreditsScene();
	Scene* (*run())(void);
	~CreditsScene();
};
