// numpuz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <conio.h>
using namespace std;
#define up 1
#define down 2
#define left 3
#define right 4


// FUNCTION
// print grid
void printg(char* arrPt, int height, int width, int cell)
{
	int idx = 0;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			printf("%s\t", arrPt);
			arrPt = arrPt + cell;
		}
		printf("\n");
	}

}

// set all cell into 0
void set0(char* arrPt, int size, int cell)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < cell - 1; j++)
		{
			sprintf_s(arrPt, cell+1, "0");
			arrPt++;
		}
		sprintf_s(arrPt, 1, "\0");
		arrPt++;
	}
}

// set number into cells
void setNum(char* pArr, int size, int cell)
{
	for (int i = 0; i < size; i++)
	{
		sprintf_s(pArr, cell+1, "%d", i+1);
		pArr = pArr + cell;
	}
}

// set numbers and a space into cells
void setNum_s(char* pArr, int size, int cell)
{
	for (int i = 0; i < size-1; i++)
	{
		sprintf_s(pArr, cell+1, "%d", i + 1);
		pArr = pArr + cell;
	}
	sprintf_s(pArr, cell+1, "%c", 129);
}

// print seperating line
void prints()
{
	printf("\n---------------\n\n");
}

// move space in puzzle
void move(int direction, int* pSpacePos, char* pArr, int height, int width, int cell)
{
	int orgPos[] = { *pSpacePos, *(pSpacePos + 1) };
	int tmpPos[] = { *pSpacePos, *(pSpacePos + 1) };

	switch (direction)
	{
		case up: 
			//printf("\ndirection: %d\n", direction);
			tmpPos[0] -= 1;
			break;
		case down:
			//printf("\ndirection: %d\n", direction);
			tmpPos[0] += 1;
			break;
		case left:
			//printf("\ndirection: %d\n", direction);
			tmpPos[1] -= 1;
			break;
		case right:
			//printf("\ndirection: %d\n", direction);
			tmpPos[1] += 1;
			break;
		default:
			printf("\nno direction\n");
	}

	if ((-1 < tmpPos[0]) & (tmpPos[0] < height) & (-1 < tmpPos[1]) & (tmpPos[1] < width))
	{
		sprintf_s(pArr + (orgPos[0] * width * cell) + orgPos[1] * cell, cell+1, "%s", pArr + (tmpPos[0] * width * cell) + tmpPos[1] * cell);
		sprintf_s(pArr + (tmpPos[0] * width * cell) + tmpPos[1] * cell, cell + 1, "%c", 129);
		*pSpacePos = tmpPos[0];
		*(pSpacePos + 1) = tmpPos[1];
	}
}


// MAIN 
//


int main()
{
	// init variables
	const int height = 3;
	const int width = 4;
	const int size = width*height;
	const int cell = 6;
	char arr[height][width][cell];
	char* arrPt;
	arrPt = &arr[0][0][0];
	int spacePos[] = {height-1, width-1}; // position is zero-based
	int* pSpacePos = &spacePos[0];
	int randTime = 20;

	// test grid and puzzle form
	/*
	set0(arrPt, size, cell);
	printg(arrPt, height, width, cell);

	setNum(arrPt, size, cell);
	prints();
	printg(arrPt, height, width, cell);

	sprintf_s(arrPt, cell+1, "11");
	prints();
	printg(arrPt, height, width, cell);
	*/
	//

	// init puzzle
	setNum_s(arrPt, size, cell);
	prints();
	printg(arrPt, height, width, cell);
	printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));
	//

	// test move
	/*
	move(up, pSpacePos, arrPt, height, width, cell);
	//move(60, pSpacePos, arrPt, height, width);
	prints();
	printg(arrPt, height, width, cell);
	printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));


	move(right, pSpacePos, arrPt, height, width, cell);
	//move(60, pSpacePos, arrPt, height, width);
	prints();
	printg(arrPt, height, width, cell);
	printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));

	move(left, pSpacePos, arrPt, height, width, cell);
	//move(60, pSpacePos, arrPt, height, width);
	prints();
	printg(arrPt, height, width, cell);
	printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));
	*/
	//

	for (int i = 0; i < randTime; i++)
	{
		//prints();
		//printf("Attemp %d", i);
		int prevPos[] = { spacePos[0], spacePos[1] };
		move((rand() % 4) + 1, pSpacePos, arrPt, height, width, cell);
		//printg(arrPt, height, width, cell);
		//printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));
		if (prevPos[0] == spacePos[0] & prevPos[1] == spacePos[1])
		{
			i--;
		}
	}

	prints();
	printg(arrPt, height, width, cell);
	printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));

	while (true)
	{
		int input = 0;
		printf("\n>>> move direction: ");
		scanf_s("%d", &input);
		if (input == 0)
		{
			break;
		}
		else
		{
			prints();
			move(input, pSpacePos, arrPt, height, width, cell);
			printg(arrPt, height, width, cell);
			printf("\nrow=%d | col=%d\n", *pSpacePos, *(pSpacePos + 1));
		}
	}

	printf("\nPress Enter to Continue\n");
	getchar();
	//free(arrPt);
	//delete(arrPt);
    return(0);
}

