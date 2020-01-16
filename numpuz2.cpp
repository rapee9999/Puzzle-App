// numpuz2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>
#include <conio.h>
#include <string.h>
#include <ctime>
#define up 1
#define down 2
#define left 3
#define right 4


struct position
{
	int row;
	int col;
};

int convertDim(int iRow, int iCol, int iWidth)
{
	return ((iRow - 1) * iWidth) + (iCol - 1);
}

class PuzzleException : public std::exception
{
	char const* what() const {
		return ("puzzle exception");
	}
};

class Puzzle
{
	#define MAX_ELEM 100
	#define PRESENT_LEN 10

	private:
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
		Puzzle() 
		{
			// default
			init(4, 4, 4, 4, 1, 1);
		}
		Puzzle(int iSetHeight, int iSetWidth, int iSetSpaceRow, int iSetSpaceCol, int iSetFocusRow, int iSetFocusCol)
		{
			init(iSetHeight, iSetWidth, iSetSpaceRow, iSetSpaceCol, iSetFocusRow, iSetFocusCol);
		}
		Puzzle(int iSetHeight, int iSetWidth, position posSetSpace, position posSetFocus)
		{
			init(iSetHeight, iSetWidth, posSetSpace, posSetFocus);
		}

		// methods
		void init(int iSetHeight, int iSetWidth, int iSetSpaceRow, int iSetSpaceCol, int iSetFocusRow, int iSetFocusCol)
		{
			// oversize
			if (((iSetHeight*iSetWidth) > MAX_ELEM) || (iSetHeight < 0) || (iSetWidth < 0))
			{
				throw ex;
			}
			// set size
			height = iSetHeight;
			width = iSetWidth;
			// clean sets
			set0(arr);
			set0(corArr);
			set0_chars(&presenters[0][0]);
			// assign sets
			setVal(arr);
			setVal(corArr);
			//setAlpha_chars(&presenters[0][0]);
			setNumber_chars(&presenters[0][0]);
			setSpace(iSetSpaceRow, iSetSpaceCol);
			setFocus(iSetFocusRow, iSetFocusCol);
		}
		void init(int iSetHeight, int iSetWidth, position posSetSpace, position posSetFocus)
		{
			// oversize
			if (((iSetHeight*iSetWidth) > MAX_ELEM) || (iSetHeight < 0) || (iSetWidth < 0))
			{
				throw ex;
			}
			// set size
			height = iSetHeight;
			width = iSetWidth;
			// clean sets
			set0(arr);
			set0(corArr);
			set0_chars(&presenters[0][0]);
			// assign sets
			setVal(arr);
			setVal(corArr);
			//setAlpha_chars(&presenters[0][0]);
			setNumber_chars(&presenters[0][0]);
			setSpace(posSetSpace.row, posSetSpace.col);
			setFocus(posSetFocus.row, posSetFocus.col);
		}

		void set0(int* arr)
		{
			for (int i = 0; i < MAX_ELEM; i++)
			{
				*(arr + i) = 0;
			}
		}

		void set0_chars(char* pChArr)
		{
			memset(pChArr, 0, MAX_ELEM*PRESENT_LEN);
		}

		void setVal(int* arr)
		{
			for (int i = 0; i < height*width; i++)
			{
				arr[i] = i + 1;
			}
		}

		void setAlpha_chars(char* pChArr)
		{
			sprintf_s(pChArr, PRESENT_LEN, "NA");
			for (int i = 1; i <= (height*width); i++)
			{
				sprintf_s(pChArr + (i * PRESENT_LEN), PRESENT_LEN, "%c", 'A' + (i - 1));
			}
		}

		void setNumber_chars(char* pChArr)
		{
			sprintf_s(pChArr, PRESENT_LEN, "NA");
			for (int i = 1; i <= (height*width); i++)
			{
				sprintf_s(pChArr + (i * PRESENT_LEN), PRESENT_LEN, "%d", i);
			}
		}

		bool setSpace(int h, int w)
		{
			if ((h > 0) && (h <= height) && (w > 0) && (w <= width))
			{
				sprintf_s(&presenters[((h-1)*width)+(w-1)+1][0], PRESENT_LEN, "%c", 129);
				spaceValue = arr[((h - 1)*width) + (w - 1)];
				spacePos[0] = h;
				spacePos[1] = w;
				return true;
			}
			else
			{
				return false;
			}
		}

		bool setFocus(int h, int w)
		{
			if ((h > 0) && (h <= height) && (w > 0) && (w <= width))
			{
				focus[0] = h;
				focus[1] = w;
				return true;
			}
			else
			{
				return false;
			}
		}

		bool setValueIdx(int idx)
		{
			if ((idx < 0) || (idx >= (height*width)))
			{
				return false;
			}
			iValIdx = idx;
			return true;
		}

		bool moveFocus(int direction)
		{
			int newFocus[2] = {focus[0], focus[1]};
			switch (direction)
			{
				case up:
					newFocus[0]--;
					break;
				case down:
					newFocus[0]++;
					break;
				case left:
					newFocus[1]--;
					break;
				case right:
					newFocus[1]++;
					break;
				default:
					return false;
			}
			if ((newFocus[0] <= 0) || (newFocus[0] > height) || (newFocus[1] <= 0) || (newFocus[1] > width))
			{
				return false;
			}
			else
			{
				focus[0] = newFocus[0];
				focus[1] = newFocus[1];
				return true;
			}
		}
		
		bool moveSpaceToFocus()
		{
			if (((spacePos[0] - 1) == focus[0]) && (spacePos[1] == focus[1])) { /*pass*/ }
			else if (((spacePos[0] + 1) == focus[0]) && (spacePos[1] == focus[1])){ /*pass*/ }
			else if (((spacePos[1] - 1) == focus[1]) && (spacePos[0] == focus[0])){ /*pass*/ }
			else if (((spacePos[1] + 1) == focus[1]) && (spacePos[0] == focus[0])){ /*pass*/ }
			else
			{
				return false;
			}
			moveSpace(focus[0], focus[1]);
			spacePos[0] = focus[0];
			spacePos[1] = focus[1];
			return true;
		}

		void moveSpace(int iNewSpaceRow, int iNewSpaceCol)
		{
			arr[((spacePos[0] - 1)*width) + spacePos[1] - 1] = arr[((iNewSpaceRow - 1)*width) + iNewSpaceCol - 1];
			arr[((iNewSpaceRow - 1)*width) + iNewSpaceCol - 1] = spaceValue;
		}

		void swap(position pos1, position pos2)
		{
			int iTempVal1 = arr[convertDim(pos1.row, pos1.col, width)];
			int iTempVal2 = arr[convertDim(pos2.row, pos2.col, width)];
		}

		void shuffle(int shufNum)
		{
			// system requires 1.Space Position 2.Array of Values 3.Height and Width 4.number of shuffling
			int neighbors[4][2]; // neighborhood space
			int possNextSpace[4][2]; // all possible next space
			int numberPoss = 0; // number of possibility
			int nextSpace[2]; // selected next space
			int prevSpace[2]; // previous space
			prevSpace[0] = spacePos[0];
			prevSpace[1] = spacePos[1];
			int random; // random value
			srand(time(NULL)); // initiate random related to time

							   // shuffling
			for (int sn = 0; sn < shufNum; sn++)
			{
				// neighberhood space position
				neighbors[0][0] = spacePos[0] - 1; neighbors[0][1] = spacePos[1]; // row--
				neighbors[1][0] = spacePos[0] + 1; neighbors[1][1] = spacePos[1]; // row++
				neighbors[2][0] = spacePos[0]; neighbors[2][1] = spacePos[1] - 1; // col--
				neighbors[3][0] = spacePos[0]; neighbors[3][1] = spacePos[1] + 1; // col++
																				  // clean possNextspace
				for (int i = 0; i < 4; i++)
				{
					possNextSpace[i][0] = 0;
					possNextSpace[i][1] = 0;
				}
				// check out of bound into possNextSpace
				numberPoss = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((neighbors[i][0] > 0) && (neighbors[i][0] <= height) && (neighbors[i][1] > 0) && (neighbors[i][1] <= width))
					{
						if ((neighbors[i][0] != prevSpace[0]) || neighbors[i][1] != prevSpace[1]) // check if not same route
						{
							possNextSpace[numberPoss][0] = neighbors[i][0];
							possNextSpace[numberPoss][1] = neighbors[i][1];
							numberPoss++;
						}
					}
				}
				// random
				random = rand() % numberPoss;
				// define next space
				nextSpace[0] = possNextSpace[random][0]; nextSpace[1] = possNextSpace[random][1];
				// moving space
				moveSpace(nextSpace[0], nextSpace[1]);

				// prepare next shuffle
				prevSpace[0] = spacePos[0];
				prevSpace[1] = spacePos[1];
				spacePos[0] = nextSpace[0];
				spacePos[1] = nextSpace[1];
				nextSpace[0] = 0; //clean
				nextSpace[1] = 0; //clean
			}
		}

		bool check()
		{
			for (int i = 0; i < height*width; i++)
			{
				if (arr[i] != corArr[i])
				{
					return false;
				}
			}
			return true;
		}

		char* val2char(int val)
		{
			return &presenters[val][0];
		}

		int getValue()
		{
			int val = arr[iValIdx];
			setValueIdx(iValIdx + 1);
			return val;
		}

		void getArr(int* receiver_arr, int receiver_size)
		{
			if (receiver_size != (height*width))
			{
				throw ex;
			}
			for (int i = 0; i < receiver_size; i++)
			{
				*receiver_arr = arr[i];
				receiver_arr++;
			}
		}

		position getSpace()
		{
			position pos;
			pos.row = spacePos[0];
			pos.col = spacePos[1];
			return pos;
		}

		position getFocus()
		{
			position pos;
			pos.row = focus[0];
			pos.col = focus[1];
			return pos;
		}

		int getHeight() { return height; }

		int getWidth() { return width; }

		int getMaxElement() { return MAX_ELEM; }

};

void printValue_grid(Puzzle pz)
{
	 int h = pz.getHeight();
	 int w = pz.getWidth();
	 pz.setValueIdx(0);
	 for (int i = 0; i < ( h * w ); i++)
	 {
		 printf("%d\t", pz.getValue());
		 if (i%w == 3)
			 {
			 printf("\n");
			 }
	 }
}

void printChar_grid(Puzzle pz)
{
	int h = pz.getHeight();
	int w = pz.getWidth();
	pz.setValueIdx(0);
	for (int i = 0; i < ( h * w ); i++)
	{
		printf("%s\t", pz.val2char(pz.getValue()));
		if ((i % w) == (w - 1))
		{
			printf("\n");
		}
	}
}

void printPuzzle(Puzzle pz)
{
	int h = pz.getHeight();
	int w = pz.getWidth();
	char ch1;
	char ch2;
	position focus = pz.getFocus();
	pz.setValueIdx(0);
	for (int i = 0; i < ( h * w ); i++)
	{
		ch1 = ' ';
		ch2 = ' ';
		if (convertDim(focus.row, focus.col, w) == i)
		{
			ch1 = '[';
			ch2 = ']';
		}
		printf("%c%s%c\t", ch1, pz.val2char(pz.getValue()), ch2);
		if ( (i % w) == (w - 1))
		{
			printf("\n");
		}
	}
}

int main()
{
	// base variables
	Puzzle pz;
	int height = 5;
	int width = 4;
	position posStartSpace = { height,width };
	position posStartFocus = { 1,1 };
	int shuffleNum = 10;

	// init puzzle
	pz.init(height, width, posStartSpace, posStartFocus);

	// shuffle puzzle
	pz.shuffle(shuffleNum);

	// display
	printf("\n");
	printPuzzle(pz);

	// input
	while (true)
	{
		if (pz.check())
		{
			break;
		}

		int input1 = _getch();

		if ((input1 == 13) || (input1 == 32)) // pressing enter or spacebar key
		{
			// test space to move status
			
			if (pz.moveSpaceToFocus())
			{
				//printf("space to move\n");

				system("CLS");
				printf("\n");
				printPuzzle(pz);
				printf("\n");
			}
			else
			{
				//printf("space NOT to move\n");
			}
			
		}
		else if (input1 != 0xE0)
		{
			break;
		}
		else
		{
			int input2 = _getch();
			int input = 0;

			switch (input2)
			{
			case 72:
				input = up;
				break;
			case 80:
				input = down;
				break;
			case 75:
				input = left;
				break;
			case 77:
				input = right;
				break;
			default:
				break;
			}

			pz.moveFocus(input);
			system("CLS");
			printf("\n");
			printPuzzle(pz);
			printf("\n");

		}
	}

	printf("- - GAME OVER - - \n\nPress Any Key to Exit...\n");
	_getch();
    return 0;
}

