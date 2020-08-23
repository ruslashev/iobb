#include "../engine/mainloop.hh"
#include "../engine/game.hh"

#define initial_winw 1280
#define initial_winh ((initial_winw * 3) / 4)

class idk : public game
{
public:
	void init()
	{
		const int winw = initial_winw, winh = initial_winh;

		w.init(winw, winh, "iobb");
	}

	void poll_events()
	{
		if (w.key_down(KEY_ESC))
			done = true;
	}

	void update(float t, float dt)
	{
	}

	void draw(float alpha)
	{
	}
};

int main()
{
	idk i;
	mainloop m(&i);

	m.run();
}

