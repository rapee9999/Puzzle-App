#pragma once

#include "stdafx.h"
#include <exception>
#include <conio.h>
#include <string.h>
#include <ctime>
#define up 1
#define down 2
#define left 3
#define right 4
#define MAX_ELEM 100
#define PRESENT_LEN 10

using namespace std;


struct position
{
	int row;
	int col;
};


int convertDim(int iRow, int iCol, int iWidth);

class PuzzleException : public std::exception
{
	char const* what() const {
		return ("puzzle exception");
	}
};

class PuzzleBase
{

protected:
	// base valiables
	int height; // decimal number (not zero-based)
	int width; // decimal number
	int arr[MAX_ELEM]; // zero-based series *value starts at 1
	int corArr[MAX_ELEM]; // zero-based series *value starts at 1
	char presenters[MAX_ELEM][PRESENT_LEN]; // map arr *zero = NA *another number = arr
	int spacePos[2] = { 0,0 }; // space position
	int spaceValue = 0; // value represented by space
	int focus[2] = { 0,0 }; // focus position
							// configurations
	int randTime = 20;
	// other components
	PuzzleException ex;
	int iValIdx = 0;


public:
	// constructor
	PuzzleBase();
	PuzzleBase(int iSetHeight, int iSetWidth, int iSetSpaceRow, int iSetSpaceCol, int iSetFocusRow, int iSetFocusCol);
	PuzzleBase(int iSetHeight, int iSetWidth, position posSetSpace, position posSetFocus);

	//deconstructor
	~PuzzleBase();

	// methods
	void init(int iSetHeight, int iSetWidth, int iSetSpaceRow, int iSetSpaceCol, int iSetFocusRow, int iSetFocusCol);
	void init(int iSetHeight, int iSetWidth, position posSetSpace, position posSetFocus);
	void set0(int* arr);
	void set0_chars(char* pChArr);
	void setVal(int* arr);
	void setAlpha_chars(char* pChArr);
	void setNumber_chars(char* pChArr);

	bool setSpace(int h, int w);

	bool setFocus(int h, int w);
	bool setValueIdx(int idx);
	bool moveFocus(int direction);

	virtual bool moveSpaceToFocus();
	void moveSpace(int iNewSpaceRow, int iNewSpaceCol);

	void swap(position pos1, position pos2);
	virtual void shuffle(int shufNum);

	bool check();

	char* val2char(int val);

	int getValue();

	void getArr(int* receiver_arr, int receiver_size);

	position getSpace();

	position getFocus();

	int getHeight();

	int getWidth();

	int getMaxElement();

};
