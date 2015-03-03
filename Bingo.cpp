#include "Bingo.h"
#include <iostream>
#include<iomanip>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;


Bingo::Bingo()
{
	row = column = 0;
	doubleArrayPtr = 0;
}
Bingo::Bingo(const  Bingo &rhs)
{
	row = rhs.row;
	column = rhs.column;
	doubleArrayPtr = NULL;
	
	doubleArrayPtr = new int * [row];
	for(int i = 0; i < row; i++)
		doubleArrayPtr[i] = new int [column];
	
	for(int i = 0; i < row; i++)
	{
		for(int j  = 0; j <column; j++)
			doubleArrayPtr[i][j] = rhs.doubleArrayPtr[i][j];
	}
} 
int Bingo::getCardSize() const
{
	return row;
}
void Bingo::createSize(int r)
{        
	//since board is a square, column and row are always =
	column = row = r;
        //double ptr points to array of int pointers
	doubleArrayPtr = new int * [row];
 	
	//this allocation creates th double ptr
	for (int i = 0; i < row; i++)
		doubleArrayPtr[i] = new int [column];
}
void Bingo::displayCard() const
{
	for (int j = 0; j < row * 6; j++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << " | " << setw(2);
                        /* all numbers that already called are set to -1
			   instead of printing -1 i print X*/
			if(doubleArrayPtr[i][j] == -1)
				cout<<'X'<<setw(2);
			else
				cout<< doubleArrayPtr[i][j] << setw(2);
		}
		cout << endl;

		for (int j = 0; j < row* 5; j++)
			cout << "-";

		cout << endl;
	}
}
void Bingo::populateCard()
{
	
	int * tempArray = new int [row];

	for (int i = 0; i < row; i++)
		tempArray[i] = -1;


	for (int j = 0; j < column; j++)
	{
		for (int i = 0; i < row; i++)
		{
			doubleArrayPtr[i][j] = rand() % 15 + (15 * j + 1);

			for (int index = 0; index < row; index++)
			{
				while (tempArray[index] == doubleArrayPtr[i][j])
				{       //this ensures unique numbers throughout the bingo board
					doubleArrayPtr[i][j] = rand() % 15 + (15 * j + 1);
					index = 0;
				}
			}
			//store the numbers in doubleArray in tempArray
			//this way we can check tempArray and see if the
			//number has been used already
			tempArray[i] = doubleArrayPtr[i][j];
		}
	}
	delete[] tempArray;
}
void Bingo::markNumber(int number)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (number == doubleArrayPtr[i][j])
				doubleArrayPtr[i][j] = -1;
		}
	}
}
bool Bingo::checkWin()
{
	int numInRow = 0;
	int j = 0;

	if (row == 1)
	{
		numInRow = -1;
		if (doubleArrayPtr[0][0] == -1)
			numInRow++;
	}
	else
	{       //this checks for a horizontal win
		//numInRow is the counter
		for (int i = 0; i < row && numInRow < row - 1; i++)
		{
			numInRow = 0;

			if (doubleArrayPtr[i][j] == doubleArrayPtr[i][j + 1])
			{
				numInRow = 1;

				for (j = 1; j < row - 1; j++)
				{
					if (doubleArrayPtr[i][j] == doubleArrayPtr[i][j + 1])
						numInRow++;
				}
			}
		}

		if (numInRow != row - 1)
		{	//checks vertical win
			numInRow = 0;
			for (int i = 0; i < row && numInRow < row - 1; i++)
			{
				numInRow = 0;
				j = 0;
				if (doubleArrayPtr[j][i] == doubleArrayPtr[j + 1][i])
				{
					numInRow = 1;

					for (j = 1; j < row - 1; j++)
					{
						if (doubleArrayPtr[j][i] == doubleArrayPtr[j + 1][i])
							numInRow++;
					}
				}
			}
		}
		//these next two check for the diagonal wins
		if (numInRow != row - 1)
		{
			numInRow = 0;
			for (int i = 0; i < row - 1; i++)
			{
				if (doubleArrayPtr[i][i] == doubleArrayPtr[i + 1][i + 1])
					numInRow++;
			}
		}

		if (numInRow != row - 1)
		{
			numInRow = 0;

			for (int i = 0, j = row - 1; i < row - 1; i++, j--)
			{
				if (doubleArrayPtr[i][j] == doubleArrayPtr[i + 1][j - 1])
					numInRow++;
			}
		}
	}
	if (numInRow == row -1)
		return true;
	else
		return false;
}
Bingo::~Bingo()
{
	for (int i = 0; i < row; i++)
		delete[] doubleArrayPtr[i];
	delete[] doubleArrayPtr;
}
