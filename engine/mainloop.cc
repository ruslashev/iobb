#include "mainloop.hh"
#include "config.hh"
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>

void mainloop::init()
{
	const int winw = initial_winw, winh = initial_winh;

	w.init(winw, winh, "iobb");
}

void mainloop::poll_events()
{
	w.poll_events();

	if (w.key_down(KEY_ESC))
		done = true;
}

void mainloop::update(float t, float dt)
{
}

void mainloop::draw(float alpha)
{
}

void mainloop::show_fps(float elapsed, uint64_t frames, float current)
{
	char title[100];

	snprintf(title, sizeof(title), "iobb avg fps %.1f inst fps %.1f dt %.2f ms",
			(double)(frames / current),
			(double)(1.f / elapsed),
			(double)(elapsed * 1000.f));

	w.set_title(title);
}

mainloop::mainloop()
{
}

void mainloop::run()
{
	init();

	const float dt = 1.f / (float)tickrate;
	const float min_frametime = 1.f / max_fps;

	float t = 0;
	float previous = w.get_time();
	float accumulator = 0;
	uint64_t frames = 0;

	done = false;

	while (!done) {
		const float current = w.get_time();
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

		done |= w.should_close();

		frames++;

		w.swap_window();

		const float frametime = (float)w.get_time() - current;

		if (frametime < min_frametime) {
			const uint64_t to_sleep = (min_frametime - frametime) * 1000.f * 1000.f * 1000.f;
			std::this_thread::sleep_for(std::chrono::nanoseconds(to_sleep));
		}
	}
}

