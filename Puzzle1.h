#pragma once


#include "PuzzleBase.h"


struct pair_position
{
	int row1;
	int col1;
	int row2;
	int col2;
};

void clearPP(pair_position* pp);


class Puzzle1 :
	public PuzzleBase
{
public:
	// recording features
	bool bRec;
	char str[100];
	pair_position ppArr[100];
	int strIdx;
	int shuffledArr[MAX_ELEM];
	int replayIdx;

	// constructor and destructor
	Puzzle1();
	~Puzzle1();

	// method
	void setRocord(bool on);
	void dump();
	void cloneArr(int* dest, int* src, int length);
	void replay();

	// overrided methodes
	virtual bool moveSpaceToFocus();
	virtual void shuffle(int shufNum);
};

