#include <windows.h>
#include <iostream>
#include "Triangle.h"

HDC hdc;

int main()
{
	system("color F0");

	HWND hwnd = GetConsoleWindow();
	if (hwnd == NULL) return 1;

	hdc = GetWindowDC(hwnd);
	if (hdc == NULL) return 1;
	
	short R = 60;

	Triangle T1(300, 200, R, 0.0f, RGB(0, 0, 255));

	Triangle T2(820, 400, R, 0.0f, RGB(0, 150, 0));

	Triangle T3(820, 700, R, 0.0f, RGB(255, 0, 0));

	short Xext2 = 700, Yext2 = 400;
	short Xext3 = 700, Yext3 = 700;

	float dfi = 0.05f;

	std::cout << "Lab 1 - Triangle (variant 7)" << std::endl;
	std::cout << "Press any key to start animation..." << std::endl;
	std::cout << "Hold SHIFT to stop." << std::endl;
	getchar();

	T1.Show();
	T2.Show();
	T3.Show();

	while (true)
	{
		T1.Rotate(dfi);
		T2.Orbit(Xext2, Yext2, dfi);
		T3.TidalLock(Xext3, Yext3, dfi);

		Sleep(30);

		if (GetKeyState(VK_SHIFT) < 0) break;
	}

	ReleaseDC(hwnd, hdc);

	return 0;
}