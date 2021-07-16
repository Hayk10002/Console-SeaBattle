#include "Player.hpp"
Player::Player() :
	frame(13, 14,
	"           1 "
	"  1234567890 "
	"  ---------- "
	"A|          |"
	"B|          |"
	"C|          |"
	"D|          |"
	"E|          |"
	"F|          |"
	"G|          |"
	"H|          |"
	"I|          |"
	"J|          |"
	"  ---------- "
)
{

}

void Player::setmappos(int x, int y)
{
	int offsetx = x - mapposx, offsety = y - mapposy;
	for (int i = 0; i < 10; i++)
	{
		ships[i].posx += offsetx;
		ships[i].posy += offsety;
	}
	mapposx = x;
	mapposy = y;

}

void Player::control(char gch)
{
	if (gch == '\t')
	{
		ships[controllingshipind].iscontrolling = 0;
		ships[controllingshipind].isfalsepos = 0;
		controllingshipind++;
		controllingshipind %= 10;
		ships[controllingshipind].iscontrolling = 1;
	}
	else if (gch == '`')
	{
		ships[controllingshipind].iscontrolling = 0;
		ships[controllingshipind].isfalsepos = 0;
		controllingshipind--;
		controllingshipind += 10 * (controllingshipind < 0);
		ships[controllingshipind].iscontrolling = 1;
	}
	else if (gch == 'n' || gch == 'N')
	{
		system("cls");
		cci.bVisible = 1;
		SetConsoleCursorInfo(conshand, &cci);
		cout << "Enter your name: ";
		cin >> name;
		if (name.size() > 23)name.erase(23, name.size() - 23);
		cci.bVisible = 0;
		SetConsoleCursorInfo(conshand, &cci);
	}
	else
	{
		setcontrol(&(ships[controllingshipind]));
		::control(gch);
	}
	Ship &csh = ships[controllingshipind];
	csh.posx += (csh.posx < mapposx + 2) * (mapposx + 2 - csh.posx);
	csh.posy += (csh.posy < mapposy + 3) * (mapposy + 3 - csh.posy);
	csh.posx += (csh.posx > mapposx + 11 - (!csh.dir) * (csh.size - 1)) * (mapposx + 11 - (!csh.dir) * (csh.size - 1) - csh.posx);
	csh.posy += (csh.posy > mapposy + 12 - (csh.dir) * (csh.size - 1)) * (mapposy + 12 - (csh.dir) * (csh.size - 1) - csh.posy);
	ships[controllingshipind].isfalsepos = 0;
	for (int i = 0; i < 10; i++)
	{
		if (i == controllingshipind) continue;
		if (iscrossing(ships[i], ships[controllingshipind])) ships[controllingshipind].isfalsepos = 1;
	}
}

void Player::draw()
{
	::draw(frame, mapposx, mapposy);
	for (int i = 0; i < 10; i++) if (i != controllingshipind) ships[i].draw();
	ships[controllingshipind].draw();
	SetConsoleCursorPosition(conshand, COORD{ short(nameposx - name.size() / 2), short(nameposy) });
	cout << name;
}

bool isplayerlosed(Player &pl)
{
	bool losed = 1;
	for (int i = 0; i < 10; i++) for (int j = 0; j < pl.ships[i].size; j++) if (pl.ships[i].isattacked.get()[j] == 0)losed = 0;
	return losed;
}

bool hittopl(Player &pl, int x, int y, int& hittedshind)
{
	for (int i = 0; i < 10; i++)
	{
		bool hit = 0;
		int index;
		if (pl.ships[i].dir == Horizontal)
		{
			if (y == pl.ships[i].posy) if (x >= pl.ships[i].posx && x < pl.ships[i].posx + pl.ships[i].size)
			{
				hit = 1;
				index = x - pl.ships[i].posx;
			}
		}
		else if (pl.ships[i].dir == Vertical)
		{
			if (x == pl.ships[i].posx) if (y >= pl.ships[i].posy && y < pl.ships[i].posy + pl.ships[i].size)
			{
				hit = 1;
				index = y - pl.ships[i].posy;
			}
		}
		if (hit)
		{
			pl.ships[i].isattacked.get()[index] = 1;
			hittedshind = i;
			return 1;
		}
	}
	return 0;
}