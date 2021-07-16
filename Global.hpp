#pragma once
#include <Windows.h>
#include <deque>
#include "Cons.hpp"
using namespace std;

extern HANDLE conshand;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;
extern CONSOLE_CURSOR_INFO cci;

extern deque<ConRect> rects;
void draw(ConTexture &t, int x, int y);
void drawrects(bool eraserects = 1);
void cls(ConPixel pix = ConPixel());