#pragma once
#include <Windows.h>
#include <string>
#include <cmath>
using namespace std;
class ConPixel
{
public:
	ConPixel()
	{
		val = (32 << 8) + 7;
		istt = 0;
	}
	ConPixel(int bc, int tc, char c)
	{
		val = (c << 8) + (bc << 4) + tc;
		istt = 0;
	}
	char gch()
	{
		return (unsigned short)(val >> 8);
	}
	int gc()
	{
		return (unsigned short)((unsigned short)(val << 8) >> 8);
	}
	int gtc()
	{
		return (unsigned short)((unsigned short)(val << 12) >> 12);
	}
	int gbc()
	{
		return (unsigned short)((unsigned short)(val << 8) >> 12);
	}
	int gv()
	{
		return val;
	}
	bool ga()
	{
		return istt;
	}
	void sch(unsigned short c)
	{
		val = gc() + (c << 8);
	}
	void sc(unsigned short c)
	{
		istt = 0;
		val = (gch() << 8) + c;
	}
	void stc(unsigned short c, bool a = 0)
	{
		istt = a;
		val = (val >> 4 << 4) + c;
	}
	void sbc(unsigned short c)
	{
		val = (val & ~(unsigned short)(15 << 4)) + (unsigned short)(c << 4);
		if (istt) stc(gbc(), 1);
	}
	void sv(unsigned short v)
	{
		val = v;
	}
	void sa()
	{
		istt = 1;
		stc(gbc(), 1);
	}
private:
	bool istt;
	unsigned short val;


};
struct ConTexture
{
	int width, height;
	shared_ptr<ConPixel> pixels;
	ConTexture(int w = 1, int h = 1, string str = " ")
	{
		width = w;
		height = h;
		pixels = shared_ptr<ConPixel>(new ConPixel[w * h]);
		for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) gpxl(j, i).sch(str[min((int)str.size() - 1, j + i * w)]);
	}
	ConPixel& gpxl(int x, int y)
	{
		x = min(x, width - 1);
		y = min(y, height - 1);
		return pixels.get()[x + y * width];
	}
	ConPixel gpxlc(int x, int y)
	{
		x = min(x, width - 1);
		y = min(y, height - 1);
		return pixels.get()[x + y * width];
	}
};
struct ConRect
{
	int x, y, w, h, bc;
};