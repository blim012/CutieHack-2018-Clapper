#include "notechecker.h"

int NoteChecker::CheckNote(Music *m)
{
	if (recording)
	{
		unsigned int DistanceFromQuarter = m->GetSongPosition() % (unsigned int)m->GetQuarter();
		unsigned int DistanceFromEighth = m->GetSongPosition() % (unsigned int)m->GetEighth();
		unsigned int DistanceFromSixteenth = m->GetSongPosition() % (unsigned int)m->GetSixteenth();

		if (DistanceFromQuarter <= 150) 
		{
			AddNote((m->GetSongPosition() - DistanceFromQuarter) + (m->GetQuarter() * 16)); //(quarter * 16) == 4 measures
			SDL_Rect note;
			note.w = 10;
			note.h = 70;
			note.y = 500;
			note.x = (m->GetSongPosition() / 4) + 140; //140
			_b->AddNoteBlock(note);
			m->PlaySound();
			return 1;
		}

		else if (DistanceFromEighth <= 150)
		{
			AddNote((m->GetSongPosition() - DistanceFromEighth) + (m->GetQuarter() * 16));
			SDL_Rect note;
			note.w = 10;
			note.h = 70;
			note.y = 500;
			note.x = (m->GetSongPosition() / 4) + 140;
			_b->AddNoteBlock(note);
			m->PlaySound();
			return 1;
		}

		else if (DistanceFromSixteenth <= 150)
		{
			AddNote((m->GetSongPosition() - DistanceFromSixteenth) + (m->GetQuarter() * 16));
			SDL_Rect note;
			note.w = 10;
			note.h = 70;
			note.y = 500;
			note.x = (m->GetSongPosition() / 4) + 140;
			_b->AddNoteBlock(note);
			m->PlaySound();
			return 1;
		}
		else return 0;
	}
	else if (PlayMode)
	{
		for (int i = 0; i < NoteQueue.size(); i++)
		{
			if ((m->GetSongPosition() < NoteQueue[i] + 100) && (NoteQueue[i] - 100 < m->GetSongPosition())) //Leeway of 90 + 90 milliseconds 
			{
				NoteQueue.erase(NoteQueue.begin() + i);
				_b->RemoveNoteBlock(i);
				m->PlaySound();
				break;
			}
		}
	}

	return 0;
}

void NoteChecker::SetMode(Music *m)
{
	unsigned int EightBarPosition = (m->GetSongPosition() - PreviousRecord);
	if (EightBarPosition >= (m->GetQuarter() * 8))
	{	
		PreviousRecord = m->GetSongPosition();
		iteration++;
		if (iteration == 1)
		{
			recording = true;
		}
		else if (iteration == 2)
		{
			recording = false;
		}
		else if (iteration == 3)
		{
			PlayMode = true;
		}
		else if (iteration == 4)
		{
			PlayMode = false;
			m->NextTurn();
			if (player == 1)
			{
				p2score += NoteQueue.size();
				player = 2;
			}
			else
			{
				p1score += NoteQueue.size();
				player = 1;
			}
			EmptyNoteQueue();
			_b->EmptyNoteBlocks();
		}
		else
		{
			m->ReplayMusic();
			PreviousRecord = 0;
			iteration = 1;
			recording = true;
		}
	}
}

void NoteChecker::EmptyNoteQueue()
{
	NoteQueue.clear();
}

void NoteChecker::AddNote(unsigned int note)
{
	NoteQueue.push_back(note);
}
