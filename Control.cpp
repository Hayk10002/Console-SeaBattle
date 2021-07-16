#include "Control.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
void* controllingobjptr = nullptr;
int NofT = 4;
shared_ptr<const type_info*> tinfs = shared_ptr<const type_info*>(new const type_info*[NofT]);
int indoft = 0;
function<void(char)> maincontrol;

int findints(const type_info& ti)
{
	for (int i = 0; i < NofT; i++) if (*(tinfs.get()[i]) == ti) return i;
	return -1;
}

void control(char a)
{
	if (*(tinfs.get()[indoft]) == typeid(nullptr_t)) maincontrol(a);
#define elsiftype(type) else if(*(tinfs.get()[indoft]) == typeid(type)) (*(type*)controllingobjptr).control(a);
	elsiftype(Player)
	elsiftype(Ship)
	elsiftype(Bullet)
#undef elsiftype
}

