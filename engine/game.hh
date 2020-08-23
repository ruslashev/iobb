#pragma once

#include "wm/wm.hh"

class game
{
public:
	wm w;
	bool done;

	virtual void init() = 0;
	virtual void update(float t, float dt) = 0;
	virtual void draw(float alpha) = 0;
};

