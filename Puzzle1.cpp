#include "stdafx.h"
#include "Puzzle1.h"


void clearPP(pair_position* pp, int length)
{
	for (int i = 0; i < length; i++)
	{
		(*(pp + i)).row1 = 0;
		(*(pp + i)).col1 = 0;
		(*(pp + i)).row2 = 0;
		(*(pp + i)).col2 = 0;
	}
}


Puzzle1::Puzzle1()
{
	bRec = true;
	strIdx = 0;
	memset(str, 0, 100);
	clearPP(&ppArr[0], 100);
	set0(shuffledArr);
	replayIdx = -1;
}


Puzzle1::~Puzzle1()
{
}


// override
bool Puzzle1::moveSpaceToFocus()
{
	ppArr[strIdx].row1 = getSpace().row;
	ppArr[strIdx].col1 = getSpace().col;
	bool result;
	result = PuzzleBase::moveSpaceToFocus();
	if (bRec && result)
	{
		ppArr[strIdx].row2 = getSpace().row;
		ppArr[strIdx].col2 = getSpace().col;
		str[strIdx++] = '*';
	}
	return result;
}

void Puzzle1::shuffle(int shufNum)
{
	PuzzleBase::shuffle(shufNum);
	int arr[MAX_ELEM];
	set0(arr);
	getArr(arr, getWidth()*getHeight());
	cloneArr(shuffledArr, arr, getWidth()*getHeight());
}


// methods

void Puzzle1::dump()
{
	if (bRec)
	{
		for (int i = 0; i < strIdx; i++)
		{
			printf("* (%d,%d)->(%d,%d) ", ppArr[i].row1, ppArr[i].col1, ppArr[i].row2, ppArr[i].col2);
		}
		printf("\n");
	}
}

void Puzzle1::cloneArr(int* dest, int* src, int length)
{
	for (int i = 0; i < length; i++)
	{
		*(dest + i) = *(src + i);
	}
}

void Puzzle1::setRocord(bool on)
{
	bRec = on;
}

void Puzzle1::replay()
{
	if (replayIdx == -1)
	{
		cloneArr(arr, shuffledArr, height*width);
		replayIdx++;
	}
	else
	{
		position p1;
		position p2;
		p1.row = ppArr[replayIdx].row1;
		p1.col = ppArr[replayIdx].col1;
		p2.row = ppArr[replayIdx].row2;
		p2.col = ppArr[replayIdx].col2;
		swap(p1, p2);
		replayIdx++;
	}
}