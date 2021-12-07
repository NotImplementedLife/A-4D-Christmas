#pragma once

class Scene
{
public:
	virtual Scene* run() = 0;
	virtual ~Scene() = default;
};