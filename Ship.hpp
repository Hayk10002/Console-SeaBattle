#pragma once
#include "Cons.hpp"
#include "Global.hpp"
using namespace std;

enum Direction { Horizontal = 0, Vertical };
class Ship
{
private:

	ConTexture t;
public:
	int size;
	int posx, posy;
	Direction dir;
	bool isfalsepos, ishidden, iscontrolling;
	shared_ptr<bool> isattacked;
	Ship(int s = 1, Direction d = Horizontal, int px = 0, int py = 0, bool isfp = 0, bool ish = 0, bool isc = 0);
	void control(char gch);
	void draw();

};

bool iscrossing(Ship &f, Ship &s);