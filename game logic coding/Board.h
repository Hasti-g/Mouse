#pragma once
#include<vector>

class Board
{
private:
	int length, width;
	std::vector< std::vector<bool>> moleVisible;

public:
	Board();
	void show_mole_at(int x , int y);
	void disappear(int x , int y);
	void hide();
	bool mole_direction(int x , int y)
	int GetWidth()const { return width; }
	int GetLength()comst { return length; }
};