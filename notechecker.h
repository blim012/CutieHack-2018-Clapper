#ifndef __NOTECHECKER
#define __NOTECHECKER

#include <vector>
#include <SDL.h>
#include "music.h"
#include "notebar.h"

class NoteChecker
{
private:
	bool recording = false;
	bool PlayMode = false;
	int player = 1;
	int p1score = 0;
	int p2score = 0;
	unsigned int PreviousRecord = 0;
	int iteration = 4;

	std::vector<unsigned int> NoteQueue;

	NoteBar *_b;

public:
	NoteChecker(NoteBar *b) : _b(b) {}
	int CheckNote(Music *m);
	void SetMode(Music *m);
	void EmptyNoteQueue();
	void AddNote(unsigned int note);
	void ResetIteration() { iteration = 4; }
	void ResetRecord() { PreviousRecord = 0; }
	int GetP1Score() { return p1score; }
	int GetP2Score() { return p2score; }
};

#endif