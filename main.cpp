#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <memory>
#include <typeinfo>
#include <deque>
#include <functional>
#include <set>
#include <ctime>
#include <cmath>
#include "Global.hpp"
#include "Cons.hpp"
#include "Ship.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
using namespace std;

//#define FASTSTART









int main()
{
	bool gameclosed = 0;
	int whowin = -1;
	GetConsoleCursorInfo(conshand, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(conshand, &cci);
	GetConsoleScreenBufferInfo(conshand, &csbi);
	
    tinfs.get()[0] = &typeid(nullptr_t);
    tinfs.get()[1] = &typeid(Player);
    tinfs.get()[2] = &typeid(Ship);
	tinfs.get()[3] = &typeid(Bullet);

	Player pls[2];
	
	auto initplayer = [&](Player &pl, string index) -> void
	{
		if(gameclosed) return;
		pl.name = "Player " + index;
		pl.nameposx = 11;
		pl.nameposy = 17;
		bool endofinit = 0;
		pl.mapposx = 10;
		maincontrol = [&](char gch)
		{


			if(gch == 27) gameclosed = 1;
			else if(gch == 13)
			{
#ifdef FASTSTART
				endofinit = 1;
#else// 
				set<int> falseposshipsind{};
				for(int i = 0; i < 10; i++) 
				{
					for(int j = 0; j < 10; j++)
					{
						if(i == j) continue;
						if(iscrossing(pl.ships[i], pl.ships[j])) falseposshipsind.insert({i, j});
					}
					if(pl.ships[i].posx < pl.mapposx) falseposshipsind.insert(i);
				}
				if(falseposshipsind.empty()) endofinit = 1;
				else 
				{
					for(auto iter = falseposshipsind.begin(); iter != falseposshipsind.end(); iter++) if((*iter) != pl.controllingshipind) pl.ships[*iter].isfalsepos = 1;
					cls();
					pl.draw();
					Sleep(200);
					for(auto iter = falseposshipsind.begin(); iter != falseposshipsind.end(); iter++) if((*iter) != pl.controllingshipind) pl.ships[*iter].isfalsepos = 0;
					cls();
					pl.draw();
					Sleep(200);
					for(auto iter = falseposshipsind.begin(); iter != falseposshipsind.end(); iter++) if((*iter) != pl.controllingshipind) pl.ships[*iter].isfalsepos = 1;
					cls();
					pl.draw();
					Sleep(200);
					for(auto iter = falseposshipsind.begin(); iter != falseposshipsind.end(); iter++) if((*iter) != pl.controllingshipind) pl.ships[*iter].isfalsepos = 0;
				}
#endif
			}
			else
			{
				setcontrol(&pl);
				control(gch);
			}
			cls();
			pl.draw();
			if(gameclosed) system("cls");
		};
		cls();
		pl.draw();
		while (!gameclosed && !endofinit)
		{
			if (_kbhit())
			{
				setcontrol<nullptr_t>(nullptr);
				control(_getch());
			}
		}
	};
	auto game = [&]() 
	{
		srand(time(0));
		for (int i = 0; i < 10; i++)
		{
			pls[0].ships[i].ishidden = 1;
			pls[1].ships[i].ishidden = 1;
		}
		pls[0].ships[pls[0].controllingshipind].iscontrolling = 0;
		pls[1].ships[pls[1].controllingshipind].iscontrolling = 0;
		pls[0].setmappos(5, 0);
		pls[1].setmappos(31, 0);
		pls[1].nameposx = 37;
		for (bool playerstep = 0;!gameclosed; playerstep = !playerstep)
		{
			bool nextstep = 0;
			Bullet bl(pls[!playerstep]);
			maincontrol = [&](char gch)
			{
				if (gch == 27) gameclosed = 1;
				if (gch == 13)
				{
					int res = bl.launch();
					nextstep = 1;
					if (isplayerlosed(pls[!playerstep]))
					{
						whowin = playerstep;
						gameclosed = 1;
					}
					if(res == 1) playerstep = !playerstep;
					if (res == -1) nextstep = 0;
					
					
				}
				else
				{
					setcontrol(&bl);
					control(gch);
				}
				cls();
				pls[0].draw();
				pls[1].draw();
				bl.draw();
				if (gameclosed) return;
			};
			cls();
			pls[0].draw();
			pls[1].draw();
			bl.draw();
			while (!gameclosed && !nextstep)
			{
				if (_kbhit())
				{
					setcontrol<nullptr_t>(nullptr);
					control(_getch());
				}
			}
		}
	};
	initplayer(pls[0], "1");
	initplayer(pls[1], "2");
	game();
	system("cls");
	if (whowin != -1)
	{
		cout << pls[whowin].name << " won the game" << endl;
		system("pause");
	}
	return 0;
}
