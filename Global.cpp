#include "Global.hpp"
HANDLE conshand = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_CURSOR_INFO cci;

deque<ConRect> rects{};

void draw(ConTexture &t, int x, int y)
{
	for (int i = 0; i < t.height; i++)
	{
		for (int j = 0; j < t.width; j++)
		{
			DWORD n = 0;
			COORD c = { short(x + j), short(y + i) };
			FillConsoleOutputAttribute(conshand, t.gpxl(j, i).gc(), 1, c, &n);
			FillConsoleOutputCharacter(conshand, t.gpxl(j, i).gch(), 1, c, &n);
		}
	}
}

void drawrects(bool eraserects)
{
	for (auto r : rects)
	{
		DWORD n;

		for (int i = 0; i < r.h; i++)
		{
			for (int j = 0; j < r.w; j++)
			{
				COORD c = { short(r.x + j), short(r.y + i) };
				WORD w;
				ReadConsoleOutputAttribute(conshand, &w, 1, c, &n);
				w <<= 12;
				w >>= 12;
				w += (unsigned short)(r.bc) << 4;
				WriteConsoleOutputAttribute(conshand, &w, 1, c, &n);
			}
		}
	}
	if (eraserects) rects.erase(rects.begin(), rects.end());
}

void cls(ConPixel pix)
{
	DWORD n, size;
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(conshand, pix.gch(), size, { 0, 0 }, &n);
	FillConsoleOutputAttribute(conshand, pix.gc(), size, { 0, 0 }, &n);
}