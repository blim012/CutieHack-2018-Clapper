#include "core.h"

Core::Core(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL_Init failed. Error: %s\n", SDL_GetError());
	}
	else
	{
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		_WindowSurface = SDL_GetWindowSurface(_window);
		if (_window == NULL)
		{
			printf("Window creation failed. Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_FillRect(_WindowSurface, NULL, SDL_MapRGB(_WindowSurface->format, 255, 255, 255));
			SDL_UpdateWindowSurface(_window);
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == NULL)
		{
			printf("Renderer creation failed. Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//Other File types init here
			if (TTF_Init() == -1)
			{
				printf("TTF failed to initialize. Error: %s\n", TTF_GetError());
			}
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("Audio channel creation failed. Error: %s\n", Mix_GetError());
		}
	}
}

Core::~Core()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_FreeSurface(_WindowSurface);

	_window = NULL;
	_WindowSurface = NULL;
	_renderer = NULL;
	
	Mix_Quit();
	SDL_Quit();
}

/*
Implement Note Color
*/

void Core::GameLoop()
{
	bool quit = false;
	bool title = true;
	Music *m = new Music();
	ScreenText *s = new ScreenText();
	NoteBar *b = new NoteBar();
	NoteChecker *n = new NoteChecker(b);

	while (title == true)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				title = false;
			}
		}
		
		SDL_RenderClear(_renderer);
		s->TitlePrint(_renderer);
		SDL_RenderPresent(_renderer);
	}

	m->PlayMusic();

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				if (title == true) title = false;
				
				if (event.key.repeat == 0)
				{
					InputHandler(&event, m, n);
				}

			default:
				break;
			}
		}


		SDL_RenderClear(_renderer);

		
		m->UpdateSongPosition();
		n->SetMode(m);
		s->DetermineText(m->GetSongPosition(), m->GetQuarter(), _renderer);
		b->RenderNoteStaff(_renderer);
		b->RenderPlayBar(_renderer, m->GetSongPosition(), m->GetQuarter());
		b->RenderNoteBlocks(_renderer);
		s->ScoreScreen(_renderer, m, n, m->GetTurns(), n->GetP1Score(), n->GetP2Score());
		
		SDL_RenderPresent(_renderer);
	}

	delete m;
	delete n;
	delete s;
	delete b;
}

void Core::InputHandler(SDL_Event *event, Music *m, NoteChecker *n)
{
	switch (event->key.keysym.sym)
	{
	case SDLK_SPACE:
		n->CheckNote(m);
		break;

	default:
		break;
	}
}
