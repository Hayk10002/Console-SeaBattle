#pragma once
#include "Global.hpp"
#include "Player.hpp"
#include "Ship.hpp"
#include "Cons.hpp"

class Bullet
{
public:
	Player &topl;
	int toposx, toposy;
	static int x, y;
	Bullet(Player &tpl);
	void control(char gch);
	void draw();
	int launch();
};