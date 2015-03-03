#ifndef BINGO_H
#define BINGO_H
class Bingo
{
private:
	int row;
	int column;
	int **doubleArrayPtr;
public:
	Bingo(int r);
	Bingo(const Bingo &rhs);
	Bingo();
	void displayCard()const;
	void populateCard();
	void createSize(int);
	int getCardSize()const;
	void markNumber(int number);
	bool checkWin();
	~Bingo();
};
#endif
