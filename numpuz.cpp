// numpuz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <conio.h>
using namespace std;


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
		sprintf_s(pArr, cell, "%d", i+1);
		pArr = pArr + cell;
	}
}


// MAIN 
//


int main()
{
	const int height = 2;
	const int width = 2;
	const int size = width*height;
	const int cell = 6;

	char arr[height][width][cell];
	char* arrPt;
	arrPt = &arr[0][0][0];
	set0(arrPt, size, cell);
	
	printg(arrPt, height, width, cell);

	setNum(arrPt, size, cell);
	printg(arrPt, height, width, cell);

	printf("Press Enter to Continue\n");
	getchar();
	//free(arrPt);
	//delete(arrPt);
    return(0);
}

