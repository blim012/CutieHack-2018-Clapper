#ifndef __NOTEBAR
#define __NOTEBAR

#include <SDL.h>
#include <stdio.h>
#include <vector>

class NoteBar
{
private:
	std::vector<SDL_Rect> NoteBlocks;
	SDL_Rect NoteStaff;
	SDL_Rect PlayBar;
	bool SpawnPlayBar = false;
	bool isBeginning = true;
	unsigned int PreviousMeasure = 0;

public:
	NoteBar();
	void RenderNoteStaff(SDL_Renderer* renderer);
	void RenderPlayBar(SDL_Renderer* renderer, unsigned int SongPosition, float quarter);
	void RenderNoteBlocks(SDL_Renderer* renderer);
	void AddNoteBlock(SDL_Rect note);
	void RemoveNoteBlock(int i);
	void EmptyNoteBlocks();
};

#endif
