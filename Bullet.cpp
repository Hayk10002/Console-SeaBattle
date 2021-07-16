#include "Bullet.hpp"

Bullet::Bullet(Player &tpl) : topl(tpl)
{
	toposx = x;
	toposy = y;
}

void Bullet::control(char gch)
{
	if (gch == 'w' || gch == 'W') toposy -= (toposy > 0);
	if (gch == 'a' || gch == 'A') toposx -= (toposx > 0);
	if (gch == 's' || gch == 'S') toposy += (toposy < 9);
	if (gch == 'd' || gch == 'D') toposx += (toposx < 9);
}

void Bullet::draw()
{
	rects.push_back(ConRect{ topl.mapposx + 2 + toposx, topl.mapposy + 3, 1, 10, 8 });
	rects.push_back(ConRect{ topl.mapposx + 2, topl.mapposy + 3 + toposy, 10, 1, 8 });
	rects.push_back(ConRect{ topl.mapposx + 2 + toposx, topl.mapposy + 3 + toposy, 1, 1, 7 });
	drawrects();
}

int Bullet::launch()
{
	x = toposx;
	y = toposy;
	int htshind;
	if (!hittopl(topl, topl.mapposx + 2 + toposx, topl.mapposy + 3 + toposy, htshind))
	{
		if (topl.frame.gpxl(toposx + 2, toposy + 3).gch() == '*') return -1;
		topl.frame.gpxl(toposx + 2, toposy + 3).sch('*');

		return 0;
	}
	topl.frame.gpxl(toposx + 2, toposy + 3).sch('*');
	bool isdead = 1;
	for (int i = 0; i < topl.ships[htshind].size; i++) if (!topl.ships[htshind].isattacked.get()[i]) isdead = 0;
	int htshx = topl.ships[htshind].posx, htshy = topl.ships[htshind].posy, htshs = topl.ships[htshind].size;
	Direction htshd = topl.ships[htshind].dir;
	if (isdead) for (int i = htshy - 1; i < htshy + htshd * (htshs - 1) + 2; i++) for (int j = htshx - 1; j < htshx + (!htshd) * (htshs - 1) + 2; j++)
	{
		int xx = j - topl.mapposx - 2;
		int yy = i - topl.mapposy - 3;
		bool isinmap = 1;
		if (xx < 0 || xx >= 10) isinmap = 0;
		if (yy < 0 || yy >= 10) isinmap = 0;
		if (isinmap) topl.frame.gpxl(xx + 2, yy + 3).sch('*');
	}
	return 1;
}

int Bullet::x = 0;
int Bullet::y = 0;