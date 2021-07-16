#pragma once
#include <iostream>
#include <string>
#include "Global.hpp"
#include "Control.hpp"
#include "Cons.hpp"
#include "Ship.hpp"
using namespace std;

class Player
{
public:
	string name = "";
	int nameposx, nameposy;
	ConTexture frame;
	Ship ships[10]{
		Ship(4, Horizontal, 12, 3, 0, 0, 1),
		Ship(3, Horizontal, 0, 2),
		Ship(3, Horizontal, 4, 2),
		Ship(2, Horizontal, 0, 4),
		Ship(2, Horizontal, 3, 4),
		Ship(2, Horizontal, 6, 4),
		Ship(1, Horizontal, 0, 6),
		Ship(1, Horizontal, 2, 6),
		Ship(1, Horizontal, 4, 6),
		Ship(1, Horizontal, 6, 6)
	};
	bool isdead[10]{ 0,0,0,0,0,0,0,0,0,0 };
	int controllingshipind = 0, mapposx = 0, mapposy = 0;
	Player();
	void setmappos(int x, int y);
	void control(char gch);
	void draw();
};
bool isplayerlosed(Player &pl);
bool hittopl(Player &pl, int x, int y, int& hittedshind);