#include <windows.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <vector>

const double Pi = 3.14159265358979323846;

void DrawLine(HDC hdc, short x1, short y1, short x2, short y2) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

HDC hdc = NULL;

class Point {
public:
    short X, Y;
    COLORREF C;
    Point(short x = 0, short y = 0, COLORREF c = RGB(0, 0, 0)) : X(x), Y(y), C(c) {}
    void Show() const {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        short R = 2, Ri;
        for (char i = -1; i < 2; ++i) {
            Ri = R * i;
            Arc(hdc, X - Ri, Y - Ri, X + Ri, Y + Ri, X, Y + Ri, X, Y + Ri);
        }
        DeleteObject(pen);
    }
};

class Line {
public:
    Point p1, p2;
    COLORREF color;
    Line(Point a = Point(), Point b = Point(), COLORREF c = RGB(0, 0, 0))
        : p1(a), p2(b), color(c) {
    }
    void Show() const {
        HPEN pen = CreatePen(PS_SOLID, 2, color);
        SelectObject(hdc, pen);
        DrawLine(hdc, p1.X, p1.Y, p2.X, p2.Y);
        DeleteObject(pen);
    }
};

class Triangle {
public:
    std::vector<Line> lines;
    COLORREF color;

    Triangle(Point bottomLeft, Point bottomRight, Point top,
        COLORREF c = RGB(0, 128, 0))
        : color(c) {

        short yMin = top.Y;
        short yMax = bottomLeft.Y;
        if (yMin > yMax) std::swap(yMin, yMax);

        for (short y = yMin; y <= yMax; ++y) {

            auto interpolate = [](Point a, Point b, short y) -> short {
                if (a.Y == b.Y) return a.X;
                return a.X + (b.X - a.X) * (y - a.Y) / (b.Y - a.Y);
                };
            short xLeft = interpolate(top, bottomLeft, y);
            short xRight = interpolate(top, bottomRight, y);
            if (xLeft > xRight) std::swap(xLeft, xRight);
            lines.push_back(Line(Point(xLeft, y, color), Point(xRight, y, color), color));
        }
    }
    void Show() const {
        for (const auto& l : lines) l.Show();
    }

    Point GetBasePoint() const {

        return lines.back().p1;
    }
};

class TriangularPrism {
public:
    std::vector<Triangle> levels;
    COLORREF color;

    TriangularPrism(Point base1, Point base2, Point base3,
        short heightLevels, COLORREF c = RGB(255, 0, 255))
        : color(c) {

        Point top((base1.X + base2.X + base3.X) / 3, base1.Y - heightLevels * 10, c);

        for (short i = 0; i <= heightLevels; ++i) {
            float t = float(i) / heightLevels;
            auto interp = [](Point a, Point b, float t) -> Point {
                return Point(a.X + (b.X - a.X) * t, a.Y + (b.Y - a.Y) * t, a.C);
                };
            Point b1 = interp(base1, top, t);
            Point b2 = interp(base2, top, t);
            Point b3 = interp(base3, top, t);

            levels.push_back(Triangle(b1, b2, b3, c));
        }
    }
    void Show() const {
        for (const auto& tri : levels) tri.Show();
    }
    Point GetBasePoint() const {
        return levels.front().GetBasePoint();
    }
};

class Point2 {
public:
    short X, Y;
    COLORREF C;
    Point2(short x = 0, short y = 0, COLORREF c = RGB(0, 0, 0)) : X(x), Y(y), C(c) {}
    void Show() const {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        short R = 2, Ri;
        for (char i = -1; i < 2; ++i) {
            Ri = R * i;
            Arc(hdc, X - Ri, Y - Ri, X + Ri, Y + Ri, X, Y + Ri, X, Y + Ri);
        }
        DeleteObject(pen);
    }
};

class Line2 {
public:
    Point2 start, end;
    COLORREF color;
    Line2(Point2 a = Point2(), Point2 b = Point2(), COLORREF c = RGB(0, 0, 0))
        : start(a), end(b), color(c) {
    }
    void Show() const {
        HPEN pen = CreatePen(PS_SOLID, 2, color);
        SelectObject(hdc, pen);
        DrawLine(hdc, start.X, start.Y, end.X, end.Y);
        DeleteObject(pen);
    }
};

class Triangle2 {
public:
    Point2 v1, v2, v3;
    COLORREF color;
    Triangle2(Point2 a, Point2 b, Point2 c, COLORREF col = RGB(0, 128, 0))
        : v1(a), v2(b), v3(c), color(col) {
    }
    void Show() const {
        HPEN pen = CreatePen(PS_SOLID, 2, color);
        SelectObject(hdc, pen);
        DrawLine(hdc, v1.X, v1.Y, v2.X, v2.Y);
        DrawLine(hdc, v2.X, v2.Y, v3.X, v3.Y);
        DrawLine(hdc, v3.X, v3.Y, v1.X, v1.Y);
        DeleteObject(pen);
    }
};

class TriangularPrism2 {
public:
    Triangle2 bottom, top;
    short height;
    COLORREF color;
    TriangularPrism2(Triangle2 bot, Triangle2 tp, short h, COLORREF c = RGB(255, 0, 255))
        : bottom(bot), top(tp), height(h), color(c) {
    }
    void Show() const {
        bottom.Show();
        top.Show();

        HPEN pen = CreatePen(PS_SOLID, 2, color);
        SelectObject(hdc, pen);
        DrawLine(hdc, bottom.v1.X, bottom.v1.Y, top.v1.X, top.v1.Y);
        DrawLine(hdc, bottom.v2.X, bottom.v2.Y, top.v2.X, top.v2.Y);
        DrawLine(hdc, bottom.v3.X, bottom.v3.Y, top.v3.X, top.v3.Y);
        DeleteObject(pen);
    }
};

int main() {
    system("color f0");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();
    hdc = GetWindowDC(hwnd);

    std::cout << "Лаб.раб.№6. Композиция. Вариант 7.\n";
    std::cout << "Часть 1: Треугольник из отрезков, призма-пирамида.\n";

    Point p1(150, 500, RGB(255, 0, 0));
    Point p2(450, 500, RGB(255, 0, 0));
    Point top(300, 200, RGB(0, 255, 0));

    Triangle tri(p1, p2, top, RGB(0, 128, 0));
    tri.Show(); getchar();

    TriangularPrism prism(p1, p2, top, 15, RGB(255, 0, 255));
    prism.Show(); getchar();

    Point basePt = prism.GetBasePoint();
    std::cout << "Координаты точки основания (левая нижняя): "
        << "X = " << basePt.X << ", Y = " << basePt.Y << "\n";

    std::cout << "\nЧасть 2: Композиция через объекты-вершины.\n";
    Point2 a(700, 400, RGB(0, 0, 255));
    Point2 b(900, 400, RGB(0, 0, 255));
    Point2 c(800, 250, RGB(0, 0, 255));
    Triangle2 tri2(a, b, c, RGB(0, 255, 255));
    tri2.Show(); getchar();

    Point2 a2(720, 350, RGB(255, 255, 0));
    Point2 b2(880, 350, RGB(255, 255, 0));
    Point2 c2(800, 200, RGB(255, 255, 0));
    Triangle2 triTop(a2, b2, c2, RGB(255, 255, 0));
    TriangularPrism2 prism2(tri2, triTop, 100, RGB(255, 0, 255));
    prism2.Show(); getchar();

    std::cout << "Координаты вершины нижнего основания: "
        << "X = " << tri2.v1.X << ", Y = " << tri2.v1.Y << "\n";

    std::cout << "\nЗавершение..."; getchar();
    CloseWindow(hwnd);
    return 0;
}
