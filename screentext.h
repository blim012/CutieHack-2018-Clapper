#ifndef __SCREENTEXT
#define __SCREENTEXT

#include <SDL.h>
#include <SDL_TTF.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "music.h"
#include "notechecker.h"
#include <string>
#include <sstream>

class ScreenText
{
private:
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* TextToPrint;
	SDL_Texture* TextTexture;
	SDL_Rect DRect;
	bool isBeginning = true;
	unsigned int PreviousValue = 0;

public:
	ScreenText();
	void TitlePrint(SDL_Renderer* renderer);
	void ScoreScreen(SDL_Renderer* renderer, Music *m, NoteChecker * n, int turns, int p1score, int p2score);
	void PrintText(const char* text, SDL_Renderer* renderer);
	void DetermineText(unsigned int SongPosition, float quarter, SDL_Renderer* renderer);
	SDL_Texture* GetTexture() { return TextTexture; }
};

#endif
