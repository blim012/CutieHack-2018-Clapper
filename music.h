#ifndef __MUSIC
#define __MUSIC

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

class Music
{
private:
	Mix_Music * bgm;
	Mix_Chunk * clap;

	unsigned int SongStart = 0 ;
	unsigned int SongPosition = 0;
	float bpm = 120;
	float quarter = 0;
	float eighth = 0;
	float sixteenth = 0;
	unsigned int PreviousBeat = 0; //For testing purposes
	int turns = 0;

public:
	Music();
	void PlayMusic();
	void ReplayMusic();
	void PlaySound();
	unsigned int GetSongPosition() { return SongPosition; }
	float GetQuarter() { return quarter; }
	float GetEighth() { return eighth; }
	float GetSixteenth() { return sixteenth; }
	void NextTurn() { turns++; }
	int GetTurns() { return turns; }
	void ResetTurns() { turns = 0; }
	void UpdateSongPosition();
};

#endif