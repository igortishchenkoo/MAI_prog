#include <windows.h>
#include <math.h>
#include <iostream>
#include <cstdlib>

const double Pi = 3.14159265358979323846;

void DrawLine(HDC hdc, short x1, short y1, short x2, short y2) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

HDC hdc = NULL;

class Point {
protected:
    short X, Y;
    size_t C;
public:

    Point(short x = 0, short y = 0, size_t c = RGB(0, 0, 0))
        : X(x), Y(y), C(c) {
    }

    short GetX() const { return X; }
    short GetY() const { return Y; }
    size_t GetC() const { return C; }
    void PutX(short x) { X = x; }
    void PutY(short y) { Y = y; }
    void PutC(size_t c) { C = c; }

    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);

        short R = 2, Ri;
        for (char i = -1; i < 2; ++i) {
            Ri = R * i;
            Arc(hdc, X - Ri, Y - Ri, X + Ri, Y + Ri, X, Y + Ri, X, Y + Ri);
        }
        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        Hide();
        PutX(nx);
        PutY(ny);
        Show();
    }
};

class Line : public Point {
protected:
    short X2, Y2;
public:

    Line(short x1, short y1, short x2, short y2, size_t c)
        : Point(x1, y1, c), X2(x2), Y2(y2) {
    }

    Line() : Point(), X2(0), Y2(0) {}

    short GetX2() const { return X2; }
    short GetY2() const { return Y2; }
    void PutX2(short x) { X2 = x; }
    void PutY2(short y) { Y2 = y; }

    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);
        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {

        short dx = nx - X;
        short dy = ny - Y;
        Hide();
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        Show();
    }

    double Length() const {
        return sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
    }
};

class Triangle : public Line {
protected:
    short X3, Y3;
public:

    Triangle(short x1, short y1, short x2, short y2,
        short x3, short y3, size_t c)
        : Line(x1, y1, x2, y2, c), X3(x3), Y3(y3) {
    }

    Triangle() : Line(), X3(0), Y3(0) {}

    short GetX3() const { return X3; }
    short GetY3() const { return Y3; }
    void PutX3(short x) { X3 = x; }
    void PutY3(short y) { Y3 = y; }

    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);
        DrawLine(hdc, X2, Y2, X3, Y3);
        DrawLine(hdc, X3, Y3, X, Y);
        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        short dx = nx - X;
        short dy = ny - Y;
        Hide();
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        X3 += dx; Y3 += dy;
        Show();
    }

    double Perimeter() const {
        double a = sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X - X3, 2.0) + pow(Y - Y3, 2.0));
        return a + b + c;
    }

    double Area() const {
        double a = sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X - X3, 2.0) + pow(Y - Y3, 2.0));
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class TriangularPrism : public Triangle {
protected:
    short Height;
public:

    TriangularPrism(short x1, short y1, short x2, short y2,
        short x3, short y3, short height, size_t c)
        : Triangle(x1, y1, x2, y2, x3, y3, c), Height(height) {
    }

    TriangularPrism() : Triangle(), Height(0) {}

    short GetHeight() const { return Height; }
    void PutHeight(short h) { Height = h; }

    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);

        DrawLine(hdc, X, Y, X2, Y2);
        DrawLine(hdc, X2, Y2, X3, Y3);
        DrawLine(hdc, X3, Y3, X, Y);

        short X1t = X, Y1t = Y - Height;
        short X2t = X2, Y2t = Y2 - Height;
        short X3t = X3, Y3t = Y3 - Height;
        DrawLine(hdc, X1t, Y1t, X2t, Y2t);
        DrawLine(hdc, X2t, Y2t, X3t, Y3t);
        DrawLine(hdc, X3t, Y3t, X1t, Y1t);

        DrawLine(hdc, X, Y, X1t, Y1t);
        DrawLine(hdc, X2, Y2, X2t, Y2t);
        DrawLine(hdc, X3, Y3, X3t, Y3t);

        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        short dx = nx - X;
        short dy = ny - Y;
        Hide();
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        X3 += dx; Y3 += dy;

        Show();
    }

    double Volume() const {
        return Area() * Height;
    }
};

int main() {
    system("color f0");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();
    hdc = GetWindowDC(hwnd);

    std::cout << "Лабораторная работа №3. Переопределение и перегрузка.\n";
    std::cout << "Вариант 7: точка - отрезок - треугольник - треугольная призма.\n\n";

    std::cout << "1. Рисование с помощью единого имени Show():\n";

    Point pt(200 + 350, 400, RGB(255, 0, 0));
    Line ln(200 + 350, 350, 350 + 350, 400, RGB(0, 0, 255));
    Triangle tr(400 + 350, 300, 500 + 350, 400,
        450 + 350, 500, RGB(0, 128, 0));
    TriangularPrism pr(550 + 350, 350, 650 + 350, 380,
        600 + 350, 450, 70, RGB(255, 0, 255));

    pt.Show();   getchar();
    ln.Show();   getchar();
    tr.Show();   getchar();
    pr.Show();   getchar();

    std::cout << "2. Перемещение объектов (MoveTo):\n";
    pt.MoveTo(300 + 350, 450); getchar();
    ln.MoveTo(250 + 350, 380); getchar();
    tr.MoveTo(450 + 350, 350); getchar();
    pr.MoveTo(600 + 350, 400); getchar();

    std::cout << "3. Конструкторы по умолчанию (объекты в левой части экрана):\n";

    Point pDef;
    Line lDef;
    Triangle tDef;
    TriangularPrism prDef;

    pDef.PutX(100); pDef.PutY(200); pDef.PutC(RGB(255, 255, 0));
    lDef.PutX(100); lDef.PutY(150); lDef.PutX2(200); lDef.PutY2(250); lDef.PutC(RGB(0, 255, 255));
    tDef.PutX(100); tDef.PutY(200); tDef.PutX2(200); tDef.PutY2(300);
    tDef.PutX3(150); tDef.PutY3(250); tDef.PutC(RGB(255, 128, 0));
    prDef.PutX(80); prDef.PutY(300); prDef.PutX2(180); prDef.PutY2(350);
    prDef.PutX3(130); prDef.PutY3(400); prDef.PutHeight(60); prDef.PutC(RGB(128, 0, 255));

    pDef.Show();    getchar();
    lDef.Show();    getchar();
    tDef.Show();    getchar();
    prDef.Show();   getchar();

    std::cout << "\nГеометрические параметры:\n";
    std::cout << "Длина отрезка: " << ln.Length() << std::endl;
    std::cout << "Периметр треугольника: " << tr.Perimeter() << std::endl;
    std::cout << "Площадь треугольника: " << tr.Area() << std::endl;
    std::cout << "Объём призмы: " << pr.Volume() << std::endl;

    std::cout << "\nНажмите любую клавишу для завершения...";
    getchar();
    CloseWindow(hwnd);
    return 0;
}
