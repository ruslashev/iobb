#include "mainloop.hh"
#include "config.hh"
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>

void mainloop::init()
{
	const int winw = initial_winw, winh = initial_winh;

	g->w.init(winw, winh, "iobb");

	g->init();
}

void mainloop::poll_events()
{
	g->w.poll_events();

	if (g->w.key_down(KEY_ESC))
		g->done = true;
}

void mainloop::update(float t, float dt)
{
	g->update(t, dt);
}

void mainloop::draw(float alpha)
{
	g->draw(alpha);
}

void mainloop::show_fps(float elapsed, uint64_t frames, float current)
{
	char title[100];

	snprintf(title, sizeof(title), "iobb avg fps %.1f inst fps %.1f dt %.2f ms",
			(double)(frames / current),
			(double)(1.f / elapsed),
			(double)(elapsed * 1000.f));

	g->w.set_title(title);
}

mainloop::mainloop(game *_g)
	: g(_g)
{
}

void mainloop::run()
{
	init();

	const float dt = 1.f / (float)tickrate;
	const float min_frametime = 1.f / max_fps;

	float t = 0;
	float previous = g->w.get_time();
	float accumulator = 0;
	uint64_t frames = 0;

	g->done = false;

	while (!g->done) {
		const float current = g->w.get_time();
		float elapsed = current - previous;

		show_fps(elapsed, frames, current);

		if (elapsed > max_frametime)
			elapsed = max_frametime;

		previous = current;

		accumulator += elapsed;

		while (accumulator >= dt) {
			poll_events();

			update(t, dt);
			t += dt;
			accumulator -= dt;
		}

		draw(accumulator / dt);

		g->done |= g->w.should_close();

		frames++;

		g->w.swap_window();

		const float frametime = (float)g->w.get_time() - current;

		if (frametime < min_frametime) {
			const uint64_t to_sleep = (min_frametime - frametime) * 1000.f * 1000.f * 1000.f;
			std::this_thread::sleep_for(std::chrono::nanoseconds(to_sleep));
		}
	}
}

