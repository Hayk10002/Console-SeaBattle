#include "Ship.hpp"
Ship::Ship(int s, Direction d, int px, int py, bool isfp, bool ish, bool isc):
	size(s), 
	dir(d), 
	t(s), 
	isattacked(new bool[s]), 
	posx(px), 
	posy(py), 
	isfalsepos(isfp), 
	ishidden(ish), 
	iscontrolling(isc)
{
	for (int i = 0; i < s; i++)
	{
		t.gpxl(i, 0).sch('#');
		isattacked.get()[i] = 0;
	}
}

void Ship::control(char gch)
{
	if (gch == 'a' || gch == 'A') posx -= (posx > 0);
	else if (gch == 'w' || gch == 'W') posy -= (posy > 0);
	else if (gch == 'd' || gch == 'D') posx++;
	else if (gch == 's' || gch == 'S') posy++;
	else if (gch == 'c' || gch == 'C') dir = Direction(!dir);
}

void Ship::draw()
{
	t.width = (!dir)*(size - 1) + 1;
	t.height = dir * (size - 1) + 1;
	for (int i = 0; i < size; i++)
	{
		if (isattacked.get()[i])
		{
			t.gpxl(!dir*i, dir*i).sch('x');
			t.gpxl(!dir*i, dir*i).stc(12);
		}
		else
		{
			t.gpxl(!dir*i, dir*i).sch('#');
			t.gpxl(!dir*i, dir*i).stc(7);
		}
		if (ishidden && !isattacked.get()[i])
		{
			t.gpxl(!dir*i, dir*i).sch(' ');
		}
		else if (!ishidden && !isattacked.get()[i])
		{
			t.gpxl(!dir*i, dir*i).sch('#');
		}
		if (iscontrolling && !isattacked.get()[i])
		{
			t.gpxl(!dir*i, dir*i).stc(10);
		}
		else if (!iscontrolling && !isattacked.get()[i])
		{
			t.gpxl(!dir*i, dir*i).stc(7);
		}
		if (isfalsepos && !isattacked.get()[i])
		{
			t.gpxl(!dir*i, dir*i).stc(12);
		}
		else if (!isfalsepos && !isattacked.get()[i] && !iscontrolling)
		{
			t.gpxl(!dir*i, dir*i).stc(7);
		}

	}
	::draw(t, posx, posy);
}

bool iscrossing(Ship &f, Ship &s)
{
	return (f.posx >= s.posx - 1 - (!f.dir)*(f.size - 1) &&
		f.posx <= s.posx + 1 + (!s.dir)*(s.size - 1) &&
		f.posy >= s.posy - 1 - (f.dir)*(f.size - 1) &&
		f.posy <= s.posy + 1 + (s.dir)*(s.size - 1));
}