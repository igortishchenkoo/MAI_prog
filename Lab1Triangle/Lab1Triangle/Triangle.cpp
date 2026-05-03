#include "Triangle.h"
#include <math.h>

extern HDC hdc;

Triangle::Triangle(short Xc, short Yc, short R, float fi, size_t color)
{
	this->Xc = Xc;
	this->Yc = Yc;
	this->R = R;
	this->fi = fi;
	this->color = color;
}

short Triangle::GetXc() { return Xc; }
short Triangle::GetYc() { return Yc; }
short Triangle::GetR() { return R; }
float Triangle::GetFi() { return fi; }

void Triangle::PutXc(short newXc) { Xc = newXc; }
void Triangle::PutYc(short newYc) { Yc = newYc; }
void Triangle::PutFi(float newFi) { fi = newFi; }

void Triangle::Show()
{
	HPEN pen = CreatePen(PS_SOLID, 2, color);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	const float TWO_PI_3 = 2.0f * 3.14159265f / 3.0f;

	short X[3], Y[3];
	for (int i = 0; i < 3; i++)
	{
		float angle = fi + i * TWO_PI_3;
		X[i] = Xc + (short)(R * sin(angle));
		Y[i] = Yc - (short)(R * cos(angle));
	}
	MoveToEx(hdc, X[0], Y[0], NULL);
	LineTo(hdc, X[1], Y[1]);
	LineTo(hdc, X[2], Y[2]);
	LineTo(hdc, X[0], Y[0]);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void Triangle::Hide()
{
	size_t tempColor = color;
	color = RGB(241, 241, 241);
	Show();
	color = tempColor;
}

void Triangle::Rotate(float dfi)
{
	Hide();
	fi += dfi;
	Show();
}

void Triangle::Orbit(short Xext, short Yext, float dfi)
{
	Hide();

	short dx = Xc - Xext;
	short dy = Yc - Yext;

	float orbitAngle = atan2((float)dy, (float)dx);

	float orbitR = sqrt((float)(dx * dx + dy * dy));

	orbitAngle += dfi;

	Xc = Xext + (short)(orbitR * cos(orbitAngle));
	Yc = Yext + (short)(orbitR * sin(orbitAngle));

	Show();
}

void Triangle::TidalLock(short Xext, short Yext, float dfi)
{
	Hide();

	short dx = Xc - Xext;
	short dy = Yc - Yext;
	float orbitAngle = atan2((float)dy, (float)dx);
	float orbitR = sqrt((float)(dx * dx + dy * dy));
	orbitAngle += dfi;

	Xc = Xext + (short)(orbitR * cos(orbitAngle));
	Yc = Yext + (short)(orbitR * sin(orbitAngle));
	fi = atan2((float)(Xext - Xc), (float)(Yext - Yc));

	Show();
}