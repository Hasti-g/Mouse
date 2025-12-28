#pragma once

class Mole
{
public:
	bool isVisible;
	int x, y; //the locatiom in board
	 
	Mole(int x, int y);
	void show();
	void hide();
		bool is_hit(int hitX, int hitY);
};