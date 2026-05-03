#include "Classes.h"
#include <math.h>

Point::Point(short x, short y, size_t color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}

short Point::GetX() { return x; }
short Point::GetY() { return y; }
size_t Point::GetColor() { return color; }
void Point::PutX(short newX) { x = newX; }
void Point::PutY(short newY) { y = newY; }
void Point::PutColor(size_t newColor) { color = newColor; }

void Point::Show()
{
	HPEN pen = CreatePen(PS_SOLID, 4, (COLORREF)color);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	Ellipse(hdc, x - 3, y - 3, x + 3, y + 3);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void Point::Hide()
{
	size_t temp = color;
	color = RGB(241, 241, 241);
	Show();
	color = temp;
}

void Point::MoveTo(short newX, short newY)
{
	Hide();
	x = newX;
	y = newY;
	Show();
}

Line::Line(short x1, short y1, short x2, short y2, size_t color)
	: Point(x1, y1, color)
{
	this->x2 = x2;
	this->y2 = y2;
}

short Line::GetX2() { return x2; }
short Line::GetY2() { return y2; }
void Line::PutX2(short newX2) { x2 = newX2; }
void Line::PutY2(short newY2) { y2 = newY2; }

void Line::DrawLine()
{
	HPEN pen = CreatePen(PS_SOLID, 2, (COLORREF)color);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void Line::HideLine()
{
	size_t temp = color;
	color = RGB(241, 241, 241);
	DrawLine();
	color = temp;
}

void Line::MoveLine(short dx, short dy)
{
	HideLine();
	x += dx;	y += dy;
	x2 += dx;	y2 += dy;
	DrawLine();
}

float Line::Length()
{
	short dx = x2 - x;
	short dy = y2 - y;
	return sqrtf((float)(dx * dx + dy * dy));
}

Triangle::Triangle(short x1, short y1, short x2, short y2,
	short x3, short y3, size_t color)
	: Line(x1, y1, x2, y2, color)
{
	this->x3 = x3;
	this->y3 = y3;
}

short Triangle::GetX3() { return x3; }
short Triangle::GetY3() { return y3; }
void Triangle::PutX3(short newX3) { x3 = newX3; }
void Triangle::PutY3(short newY3) { y3 = newY3; }

void Triangle::DrawTri()
{
	HPEN pen = CreatePen(PS_SOLID, 2, (COLORREF)color);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x, y);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void Triangle::HideTri()
{
	size_t temp = color;
	color = RGB(241, 241, 241);
	DrawTri();
	color = temp;
}

void Triangle::MoveTri(short dx, short dy)
{
	HideTri();
	x += dx;  y += dy;
	x2 += dx;  y2 += dy;
	x3 += dx;  y3 += dy;
	DrawTri();
}

float Triangle::Area()
{
	float s = (float)(x * (y2 - y3) + x2 * (y3 - y) + x3 * (y - y2));
	return fabsf(s) / 2.0f;
}

TriPrism::TriPrism(short x1, short y1, short x2, short y2,
	short x3, short y3, size_t color, short H)
	: Triangle(x1, y1, x2, y2, x3, y3, color)
{
	this->H = H;
}

short TriPrism::GetH() { return H; }
void TriPrism::PutH(short newH) { H = newH; }

void TriPrism::DrawPrism()
{
	HPEN pen = CreatePen(PS_SOLID, 2, (COLORREF)color);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	short shift = H;

	short bx1 = x + shift, by1 = y - shift;
	short bx2 = x2 + shift, by2 = y2 - shift;
	short bx3 = x3 + shift, by3 = y3 - shift;

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x, y);

	MoveToEx(hdc, bx1, by1, NULL);
	LineTo(hdc, bx2, by2);
	LineTo(hdc, bx3, by3);
	LineTo(hdc, bx1, by1);

	MoveToEx(hdc, x, y, NULL);  LineTo(hdc, bx1, by1);
	MoveToEx(hdc, x2, y2, NULL);  LineTo(hdc, bx2, by2);
	MoveToEx(hdc, x3, y3, NULL);  LineTo(hdc, bx3, by3);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void TriPrism::HidePrism()
{
	size_t temp = color;
	color = RGB(241, 241, 241);
	DrawPrism();
	color = temp;
}

void TriPrism::MovePrism(short dx, short dy)
{
	HidePrism();
	x += dx;  y += dy;
	x2 += dx;  y2 += dy;
	x3 += dx;  y3 += dy;
	DrawPrism();
}

float TriPrism::Volume()
{
	return Area() * (float)H;
}