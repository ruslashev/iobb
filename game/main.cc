#include <cstdio>
#include "../engine/wm/wm.hh"

int main()
{
	wm w;

	w.init(1280, 760, "iobb");

	while (!w.should_close()) {
		w.poll_events();

		if (w.key_down(KEY_ESC))
			break;

		w.swap_window();
	}
}

