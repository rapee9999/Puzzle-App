// numpuz2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>
#include <conio.h>


// CLASS
//
#define MAX_ELEM 100

class puzzleException : public std::exception
{
	char const* what() const {
		return ("eeeee");
	}

};

class puzzle
{
	private:
		int height;
		int width;
		int arr[MAX_ELEM];
		puzzleException ex;

	public:
		puzzle(int set_height, int set_width)
		{

			if ((set_height*set_height) > MAX_ELEM)
			{

			}
			height = set_height;
			width = set_width;
		}

		void init()
		{

		}

		int getHeight()
		{
			return height;
		}

		int getWidth()
		{
			return width;
		}

		int getMaxElement()
		{
			return MAX_ELEM;
		}

};


int main()
{
	puzzleException ex;
	

	try
	{
		throw ex;
	}
	catch (std::exception& e)
	{
		printf("%s\n", e.what());
	}

	_getch();
    return 0;
}

