#include "screentext.h"

ScreenText::ScreenText()
{
	font = TTF_OpenFont("lazy.ttf", 40); //Directory / size
	color = { 0, 0, 0 };
	DRect.y = 90;
	DRect.w = 600;
	DRect.x = (1280 / 2) - (DRect.w / 2);
	DRect.h = 200;
}

void ScreenText::TitlePrint(SDL_Renderer* renderer)
{
	PrintText("Press Any Key To Play!", renderer);
}

void ScreenText::ScoreScreen(SDL_Renderer* renderer, Music* m, NoteChecker *n, int turns, int p1score, int p2score)
{
	if (turns >= 4)
	{
		SDL_Event event;
		char *text;
		Mix_HaltMusic();
		if (p1score < p2score)
		{
			text = "Player 1 wins!";
		}
		else if(p1score == p2score)
		{
			text = "It's a tie!";
		}
		else
		{
			text = "Player 2 wins!";
		}
		while (1)
		{
			SDL_RenderClear(renderer);
			PrintText(text, renderer);
			SDL_RenderPresent(renderer);
		}
	}
}

void ScreenText::PrintText(const char* text, SDL_Renderer* renderer)
{
	TextToPrint = TTF_RenderText_Solid(font, text, color);
	if (TextToPrint == NULL)
	{
		printf("Text Surface failed to load\n");
	}
	else
	{
		TextTexture = SDL_CreateTextureFromSurface(renderer, TextToPrint);
		if (TextTexture == NULL)
		{
			printf("Texture Text failed to load\n");
		}
		
		SDL_RenderCopy(renderer, TextTexture, NULL, &DRect);

		SDL_FreeSurface(TextToPrint);
	}
}

void ScreenText::DetermineText(unsigned int SongPosition, float quarter, SDL_Renderer* renderer)
{
	if (isBeginning == true)
	{
		if (SongPosition < PreviousValue)
		{
			isBeginning = false;
		}
		else if (SongPosition >= ((unsigned int)quarter * 5) && SongPosition < ((unsigned int)quarter * 6))
		{
			PrintText("Record! 3", renderer);
		}
		else if (SongPosition >= (quarter * 6) && SongPosition < (quarter * 7))
		{
			PrintText("Record! 2", renderer);
		}
		else if (SongPosition >= (quarter * 7) && SongPosition < (quarter * 8))
		{
			PrintText("Record! 1", renderer);
		}
		PreviousValue = SongPosition;
	}
	else
	{
		if ((SongPosition >= (quarter * 13) && SongPosition < (quarter * 14)))
		{
			PrintText("Play! 3", renderer);
		}
		else if ((SongPosition >= (quarter * 14) && SongPosition < (quarter * 15)))
		{
			PrintText("Play! 2", renderer);
		}
		else if ((SongPosition >= (quarter * 15) && SongPosition < (quarter * 16)))
		{
			PrintText("Play! 1", renderer);
		}
		else if ((SongPosition >= (quarter * 29) && SongPosition < (quarter * 30)))
		{
			PrintText("Record! 3", renderer);
		}
		else if ((SongPosition >= (quarter * 30) && SongPosition < (quarter * 31)))
		{
			PrintText("Record! 2", renderer);
		}
		else if ((SongPosition >= (quarter * 31) && SongPosition < (quarter * 32)))
		{
			PrintText("Record! 1", renderer);
		}
	}
}