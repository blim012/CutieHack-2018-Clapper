#include "notebar.h"

NoteBar::NoteBar()
{
	NoteStaff.w = 1000;
	NoteStaff.h = 10;
	NoteStaff.y = 560;
	NoteStaff.x = (1280 / 2) - (NoteStaff.w / 2);

	PlayBar.w = 11;
	PlayBar.h = 70;
	PlayBar.y = 500;
	PlayBar.x = 0;
}

void NoteBar::RenderNoteStaff(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(renderer, &NoteStaff);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void NoteBar::RenderPlayBar(SDL_Renderer* renderer, unsigned int SongPosition, float quarter)
{
	unsigned int check = SongPosition;
	if (isBeginning == true)
	{
		check = check / ((unsigned int)quarter * 8);
		if (check != 0)
		{
			isBeginning = false;
		}
	}
	else 
	{
		check = check / ((unsigned int)quarter * 8);
		if (check == PreviousMeasure)
		{
			if (check != 0)
			{
				PlayBar.x = ((SongPosition / 4) - (1000 * check)) + 150; 
			}
			else PlayBar.x = (SongPosition / 4) + 150;
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer, &PlayBar);
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
		else if (check == 1) 
		{
			PreviousMeasure = 2;
		}
		else if(check == 3)
		{
			PreviousMeasure = 0;
		}
	}
}
void NoteBar::RenderNoteBlocks(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	for (int i = 0; i < NoteBlocks.size(); i++)
	{
		SDL_RenderFillRect(renderer, &NoteBlocks[i]);
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void NoteBar::AddNoteBlock(SDL_Rect note)
{
	NoteBlocks.push_back(note);
}

void NoteBar::RemoveNoteBlock(int i)
{
	NoteBlocks.erase(NoteBlocks.begin() + i);
}

void NoteBar::EmptyNoteBlocks()
{
	NoteBlocks.clear();
}