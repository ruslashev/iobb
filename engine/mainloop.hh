#pragma once

#include "wm/wm.hh"

class mainloop
{
	wm w;

	bool done;

	void init();
	void poll_events();
	void update(float t, float dt);
	void draw(float alpha);

	void show_fps(float elapsed, uint64_t frames, float current);
public:
	mainloop();
	void run();
};

