#pragma once
#include <windows.h>

class Triangle
{
private:
	short Xc, Yc;
	short R;
	float fi;
	size_t color;

public:
	Triangle(short Xc, short Yc, short R, float fi, size_t color);

	short GetXc();
	short GetYc();
	short GetR();
	float GetFi();

	void PutXc(short newXc);
	void PutYc(short newYc);
	void PutFi(float newFi);

	void Show();
	void Hide();

	void Rotate(float dfi);
	void Orbit(short Xext, short Yext, float dfi);
	void TidalLock(short Xext, short Yext, float dfi);

};