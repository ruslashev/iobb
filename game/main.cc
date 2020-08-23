#include <cstdio>
#include "../engine/wm/wm.hh"
#include "../engine/config.hh"

int main()
{
	wm w;

	w.init(initial_winw, initial_winh, "iobb");

	while (!w.should_close()) {
		w.poll_events();

		if (w.key_down(KEY_ESC))
			break;

		w.swap_window();
	}
}

