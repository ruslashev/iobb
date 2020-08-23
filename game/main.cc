#include "../engine/mainloop.hh"
#include "../engine/game.hh"

class idk : public game
{
public:
	void init()
	{
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

