#include "music.h"

Music::Music()
{
	bgm = Mix_LoadMUS("bgm.wav");
	clap = Mix_LoadWAV("clap.wav");

	quarter = (60 / bpm) * 1000;
	eighth = quarter / 2;
	sixteenth = eighth / 2;
}

void Music::PlayMusic()
{
	SongStart = SDL_GetTicks();
	Mix_PlayMusic(bgm, -1);
}

void Music::ReplayMusic()
{
	SongStart = SDL_GetTicks();
}

void Music::PlaySound()
{
	Mix_PlayChannel(-1, clap, 0);
}

void Music::UpdateSongPosition()
{
	SongPosition = SDL_GetTicks() - SongStart;
	unsigned int check = SongPosition;
	check = check / (int)quarter;
	if (check != PreviousBeat) //Assist Tick
	{
		//PlaySound();
		PreviousBeat = check;
	}
}

