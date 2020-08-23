#pragma once

class game
{
public:
	bool done;

	virtual void init() = 0;
	virtual void update(float t, float dt) = 0;
	virtual void draw(float alpha) = 0;
};

