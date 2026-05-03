#pragma once
#include <windows.h>

class Point
{
protected:
	short x, y;
	size_t color;
public:
	Point(short x, short y, size_t color);

	short GetX();
	short GetY();
	size_t GetColor();
	void PutX(short newX);
	void PutY(short newY);
	void PutColor(size_t newColor);

	void Show();
	void Hide();
	void MoveTo(short newX, short newY);
};

class Line : public Point
{
protected:
	short x2, y2;
public:
	Line(short x1, short y1, short x2, short y2, size_t color);

	short GetX2();
	short GetY2();
	void PutX2(short newX2);
	void PutY2(short newY2);

	void DrawLine();
	void HideLine();
	void MoveLine(short dx, short dy);

	float Length();
};

class Triangle : public Line
{
protected:
	short x3, y3;
public:
	Triangle(short x1, short y1, short x2, short y2,
		short x3, short y3, size_t color);
	short GetX3();
	short GetY3();
	void PutX3(short newX3);
	void PutY3(short newY3);

	void DrawTri();
	void HideTri();
	void MoveTri(short dx, short dy);

	float Area();
};

class TriPrism : public Triangle
{
protected:
	short H;
public:
	TriPrism(short x1, short y1, short x2, short y2,
		short x3, short y3, size_t color, short H);

	short GetH();
	void PutH(short newH);

	void DrawPrism();
	void HidePrism();
	void MovePrism(short dx, short dy);

	float Volume();
};

extern HDC hdc;