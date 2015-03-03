#include"Bingo.h"
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
using namespace std;

int callNumber(int, vector<int> &v );

int main()
{        
	vector<int> trackNumbers;
	srand((unsigned)time(NULL));
	int cardNumber, size;
	char key , wantToPlay;

	cout << "Want to play Bingo? ";
	cin >> wantToPlay;
	cout << "Enter number of cards to play with: ";
	cin >> cardNumber;
	
	//dynamically allocate array of bingo objects
	Bingo *bingo = new Bingo[cardNumber];
	Bingo bingo2;
	bingo2.createSize(6);
	bingo2.populateCard();
	bingo2.displayCard();

	while (toupper(wantToPlay) == 'Y')
	{
		bool win = false;

		cout << "enter card size: ";
		cin >> size;

		for (int i = 0; i < cardNumber; i++)
		{
			bingo[i].createSize(size);
			bingo[i].populateCard();
			bingo[i].displayCard();
		}
		do
		{
			cout << "hit y to have a number drawn: ";
			cin >> key;

			int number = callNumber(bingo[0].getCardSize(),trackNumbers );
			
			for (int i = 0; i < cardNumber; i++)
			{
				bingo[i].markNumber(number);
				bingo[i].displayCard();
				

				if (bingo[i].checkWin())
				{
					win = true;
					cout << " B " << " I " << " N " << " G " << " O !!!" << endl;
				}
			}
			cout << "The Number is... " << number << endl;
			cout << "____________________________________" << endl << endl;
		} while (!win);

		
		cout << "\nPlay Again ? ";
		cin >> wantToPlay;

		if (toupper(wantToPlay) == 'Y')
		{       
			//deallocate the bingo class array
			delete [] bingo;
			//clear number storage vect 
			trackNumbers.clear();
			cout << "Enter number of cards to play with: ";
			cin >> cardNumber;
			bingo = new Bingo[cardNumber];
		}
	}
	
	return 0;

}
int callNumber(int size, vector<int> &v)
{
	int number = (rand() % (15 * size - 1) + 1);
	
	//storing used numbers in a vect to not call the same one twice
	for(int i = 0; i < v.size(); i++)
	{       
		bool alreadyCalled = false;

		while(v[i] == number)
		{
			number = (rand() % (15 * size-1)+1);
			alreadyCalled = true;
		}
		if(alreadyCalled == true)
			i = 0;

	}
	v.push_back(number);
	return number;
}






