#include"Board.h"

Board::Board() : moleVisible(size , std::vector<bool>(size , false)) {}

void Board::show_mole_at(int x, int y)
{
	if(x >= 0 && x < size && y >= 0 && y < size)
		moleVisible[x][y] = true;
}

void Board::disapear(int x, int y)
{
	if (x >= 0 && x < size && y >= 0 && y < size)
		moleVisible[x][y] = false;
}

void Board::hide()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			moleVisible[i][j] = false;
}

bool Board::Print()const
{
	for(int i = 0 ; i < size ; i++)
		for(int j = 0 ; j < size ; j++)
}