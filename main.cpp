#include <SDL.h>
#undef main
#include <SDL_mixer.h>
#include "core.h"

int main()
{
	Core *c = new Core("Clapper", 1280, 720);

	c->GameLoop();

	c->~Core();

	return 0;
}