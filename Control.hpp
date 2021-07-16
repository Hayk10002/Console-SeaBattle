#pragma once
#include <memory>
#include <functional>
using namespace std;
extern void* controllingobjptr;
extern int NofT;
extern shared_ptr<const type_info*> tinfs;
extern int indoft;
extern function<void(char)> maincontrol;

int findints(const type_info& ti);

template<class T>
bool setcontrol(T* ptr)
{
	if (findints(typeid(T)) == -1) return 0;
	indoft = findints(typeid(T));
	controllingobjptr = ptr;
	return 1;
}

void control(char);




