// puzzle_app_sln.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "PuzzleBase.h"
#include "Puzzle1.h"



void printPuzzle(PuzzleBase pz)
{
	int h = pz.getHeight();
	int w = pz.getWidth();
	char ch1;
	char ch2;
	position focus = pz.getFocus();
	pz.setValueIdx(0);
	for (int i = 0; i < (h * w); i++)
	{
		ch1 = ' ';
		ch2 = ' ';
		if (convertDim(focus.row, focus.col, w) == i)
		{
			ch1 = '[';
			ch2 = ']';
		}
		printf("%c%s%c\t", ch1, pz.val2char(pz.getValue()), ch2);
		if ((i % w) == (w - 1))
		{
			printf("\n");
		}
	}
}

int main()
{
	// base variables
	Puzzle1 pz;



	int height = 4;
	int width = 4;
	position posStartSpace = { height,width };
	position posStartFocus = { 1,1 };
	int shuffleNum = 20;

	// init puzzle
	pz.init(height, width, posStartSpace, posStartFocus);

	// shuffle puzzle
	pz.shuffle(shuffleNum);
	/*
	for (int i = 0; i < width*height; i++)
	{
		printf("%d ", pz.shuffledArr[i]);
	}
	*/
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
				//printf("\n");
				//pz.dump();
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
			//printf("\n");
			//pz.dump();

		}
	}

	printf("\n- - GAME OVER - - \n\nPress Any Key to Continue...\n");
	_getch();

	pz.replay();
	system("CLS");
	printf("\n");
	printPuzzle(pz);

	for (int i = 0; i < pz.strIdx; i++)
	{
 		_getch();
		pz.replay();
		system("CLS");
		printf("\n");
		printPuzzle(pz);
	}

	printf("\n- - GAME OVER - - \n\nPress Any Key to Exit...\n");
	_getch();

	return 0;
}

