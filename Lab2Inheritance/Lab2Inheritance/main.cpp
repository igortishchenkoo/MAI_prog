#include <windows.h>
#include <iostream>
#include "Classes.h"

HDC hdc;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    SetConsoleCP(1251);
    system("color F0");

    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL) return 1;
    hdc = GetWindowDC(hwnd);
    if (hdc == NULL) return 1;

    std::cout << "Lab 2 - Inheritance (variant 7)" << std::endl;
    std::cout << "Hierarchy: Point -> Line -> Triangle -> TriPrism" << std::endl;
    std::cout << std::endl;

    int SHIFT = 800;

    Point p(100 + SHIFT, 100, RGB(255, 0, 0));
    Line l(100 + SHIFT, 100, 200 + SHIFT, 200, RGB(0, 255, 0));
    Triangle t(100 + SHIFT, 100, 200 + SHIFT, 200, 150 + SHIFT, 300, RGB(0, 0, 255));
    TriPrism tp(100 + SHIFT, 100, 200 + SHIFT, 200, 150 + SHIFT, 300, RGB(0, 0, 0), 50);

    std::cout << "Press ENTER to draw objects..." << std::endl;
    getchar();

    p.Show();
    l.DrawLine();
    t.DrawTri();
    tp.DrawPrism();

    std::cout << std::endl << "=== Geometric parameters ===" << std::endl;
    std::cout << "Line length:    " << l.Length() << std::endl;
    std::cout << "Triangle area:  " << t.Area() << std::endl;
    std::cout << "Prism volume:   " << tp.Volume() << " (= Area * H)" << std::endl;

    std::cout << std::endl << "Press ENTER to demonstrate movement..." << std::endl;
    getchar();

    for (int i = 0; i < 30; i++)
    {
        p.MoveTo(p.GetX() + 3, p.GetY() + 2);
        l.MoveLine(2, 3);
        t.MoveTri(3, 2);
        tp.MovePrism(-2, 3);
        Sleep(40);
    }

    std::cout << std::endl
        << "=== Demonstration of inherited (incorrect) methods ===" << std::endl
        << "When we call Show() on a Triangle, it draws ONLY a point" << std::endl
        << "(inherited from Point), not the whole triangle." << std::endl;

    std::cout << std::endl << "Press ENTER to see..." << std::endl;
    getchar();

    Triangle T2(100 + SHIFT, 480, 220 + SHIFT, 480, 160 + SHIFT, 580, RGB(255, 100, 0));
    T2.Show();

    std::cout << std::endl << "Now compare with the correct DrawTri():" << std::endl;
    std::cout << "Press ENTER..." << std::endl;
    getchar();

    Triangle T3(280 + SHIFT, 480, 400 + SHIFT, 480, 340 + SHIFT, 580, RGB(0, 100, 200));
    T3.DrawTri();

    std::cout << std::endl << "Press ENTER to exit..." << std::endl;
    getchar();

    ReleaseDC(hwnd, hdc);
    return 0;
}