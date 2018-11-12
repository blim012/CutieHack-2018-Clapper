#ifndef __CORE
#define __CORE

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>
#include <stdio.h>
#include "music.h"
#include "notechecker.h"
#include "screentext.h"
#include "notebar.h"

class Core
{
private:
	SDL_Window * _window;
	SDL_Surface * _WindowSurface;
	SDL_Renderer * _renderer;
	SDL_Event event;

public:
	Core(const char* title, int width, int height);
	~Core();
	
	void GameLoop();
	void InputHandler(SDL_Event *event, Music *m, NoteChecker *n);
};

#endif
