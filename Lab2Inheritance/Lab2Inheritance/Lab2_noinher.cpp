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

class PointInd {
private:
    short X, Y;
    size_t C;
public:

    PointInd(short x = 0, short y = 0, size_t c = RGB(0, 0, 0))
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

class LineInd {
private:
    short X1, Y1;
    short X2, Y2;
    size_t C;
public:
    LineInd(short x1, short y1, short x2, short y2, size_t c)
        : X1(x1), Y1(y1), X2(x2), Y2(y2), C(c) {
    }

    short GetX1() const { return X1; }
    short GetY1() const { return Y1; }
    short GetX2() const { return X2; }
    short GetY2() const { return Y2; }
    size_t GetC() const { return C; }
    void PutX1(short x) { X1 = x; }
    void PutY1(short y) { Y1 = y; }
    void PutX2(short x) { X2 = x; }
    void PutY2(short y) { Y2 = y; }
    void PutC(size_t c) { C = c; }

    void DrawLine() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        ::DrawLine(hdc, X1, Y1, X2, Y2);
        DeleteObject(pen);
    }

    void CleanLine() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        DrawLine();
        C = oldC;
    }

    void MoveLine(short dx, short dy) {
        CleanLine();
        X1 += dx; Y1 += dy;
        X2 += dx; Y2 += dy;
        DrawLine();
    }

    double Length() const {
        return sqrt(pow(X2 - X1, 2.0) + pow(Y2 - Y1, 2.0));
    }
};

class TriangleInd {
private:
    short X1, Y1;
    short X2, Y2;
    short X3, Y3;
    size_t C;
public:
    TriangleInd(short x1, short y1, short x2, short y2,
        short x3, short y3, size_t c)
        : X1(x1), Y1(y1), X2(x2), Y2(y2), X3(x3), Y3(y3), C(c) {
    }

    short GetX1() const { return X1; } short GetY1() const { return Y1; }
    short GetX2() const { return X2; } short GetY2() const { return Y2; }
    short GetX3() const { return X3; } short GetY3() const { return Y3; }
    size_t GetC() const { return C; }
    void PutX1(short x) { X1 = x; } void PutY1(short y) { Y1 = y; }
    void PutX2(short x) { X2 = x; } void PutY2(short y) { Y2 = y; }
    void PutX3(short x) { X3 = x; } void PutY3(short y) { Y3 = y; }
    void PutC(size_t c) { C = c; }

    void DrawTri() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        ::DrawLine(hdc, X1, Y1, X2, Y2);
        ::DrawLine(hdc, X2, Y2, X3, Y3);
        ::DrawLine(hdc, X3, Y3, X1, Y1);
        DeleteObject(pen);
    }

    void CleanTri() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        DrawTri();
        C = oldC;
    }

    void MoveTri(short dx, short dy) {
        CleanTri();
        X1 += dx; Y1 += dy;
        X2 += dx; Y2 += dy;
        X3 += dx; Y3 += dy;
        DrawTri();
    }

    double Perimeter() const {
        double a = sqrt(pow(X2 - X1, 2.0) + pow(Y2 - Y1, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X1 - X3, 2.0) + pow(Y1 - Y3, 2.0));
        return a + b + c;
    }

    double Area() const {
        double a = sqrt(pow(X2 - X1, 2.0) + pow(Y2 - Y1, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X1 - X3, 2.0) + pow(Y1 - Y3, 2.0));
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class TriPrismInd {
private:

    short X1b, Y1b, X2b, Y2b, X3b, Y3b;

    short X1t, Y1t, X2t, Y2t, X3t, Y3t;
    size_t C;
public:
    TriPrismInd(short x1, short y1, short x2, short y2,
        short x3, short y3, short height, size_t c)
        : X1b(x1), Y1b(y1), X2b(x2), Y2b(y2), X3b(x3), Y3b(y3), C(c) {

        X1t = x1; Y1t = y1 - height / 2;
        X2t = x2; Y2t = y2 - height / 2;
        X3t = x3; Y3t = y3 - height / 2;
    }

    short GetX1b() const { return X1b; } short GetY1b() const { return Y1b; }
    short GetX2b() const { return X2b; } short GetY2b() const { return Y2b; }
    short GetX3b() const { return X3b; } short GetY3b() const { return Y3b; }
    short GetX1t() const { return X1t; } short GetY1t() const { return Y1t; }
    short GetX2t() const { return X2t; } short GetY2t() const { return Y2t; }
    short GetX3t() const { return X3t; } short GetY3t() const { return Y3t; }
    size_t GetC() const { return C; }

    void PutX1b(short x) { X1b = x; } void PutY1b(short y) { Y1b = y; }
    void PutX2b(short x) { X2b = x; } void PutY2b(short y) { Y2b = y; }
    void PutX3b(short x) { X3b = x; } void PutY3b(short y) { Y3b = y; }
    void PutX1t(short x) { X1t = x; } void PutY1t(short y) { Y1t = y; }
    void PutX2t(short x) { X2t = x; } void PutY2t(short y) { Y2t = y; }
    void PutX3t(short x) { X3t = x; } void PutY3t(short y) { Y3t = y; }
    void PutC(size_t c) { C = c; }

    void DrawPrism() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);

        ::DrawLine(hdc, X1b, Y1b, X2b, Y2b);
        ::DrawLine(hdc, X2b, Y2b, X3b, Y3b);
        ::DrawLine(hdc, X3b, Y3b, X1b, Y1b);

        ::DrawLine(hdc, X1t, Y1t, X2t, Y2t);
        ::DrawLine(hdc, X2t, Y2t, X3t, Y3t);
        ::DrawLine(hdc, X3t, Y3t, X1t, Y1t);

        ::DrawLine(hdc, X1b, Y1b, X1t, Y1t);
        ::DrawLine(hdc, X2b, Y2b, X2t, Y2t);
        ::DrawLine(hdc, X3b, Y3b, X3t, Y3t);
        DeleteObject(pen);
    }

    void CleanPrism() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        DrawPrism();
        C = oldC;
    }

    void MovePrism(short dx, short dy) {
        CleanPrism();
        X1b += dx; Y1b += dy; X2b += dx; Y2b += dy; X3b += dx; Y3b += dy;
        X1t += dx; Y1t += dy; X2t += dx; Y2t += dy; X3t += dx; Y3t += dy;
        DrawPrism();
    }

    double Volume() const {
        double a = sqrt(pow(X2b - X1b, 2.0) + pow(Y2b - Y1b, 2.0));
        double b = sqrt(pow(X3b - X2b, 2.0) + pow(Y3b - Y2b, 2.0));
        double c = sqrt(pow(X1b - X3b, 2.0) + pow(Y1b - Y3b, 2.0));
        double p = (a + b + c) / 2.0;
        double baseArea = sqrt(p * (p - a) * (p - b) * (p - c));
        double height = fabs(Y1b - Y1t);
        return baseArea * height;
    }
};

int main() {
    system("color f0");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();
    hdc = GetWindowDC(hwnd);

    std::cout << "Лаб.раб.№2. Без наследования. Вариант 7\n";

    PointInd p1(200 + 350, 200, RGB(255, 0, 0));
    LineInd l1(200 + 350, 150, 350 + 350, 200, RGB(0, 0, 255));
    TriangleInd t1(400 + 350, 100, 500 + 350, 200,
        450 + 350, 300, RGB(0, 128, 0));
    TriPrismInd pr1(550 + 350, 150, 650 + 350, 180,
        600 + 350, 250, 80, RGB(255, 0, 255));

    std::cout << "1. Рисование объектов:\n";
    p1.Show();          getchar();
    l1.DrawLine();      getchar();
    t1.DrawTri();       getchar();
    pr1.DrawPrism();    getchar();

    std::cout << "2. Движение объектов:\n";
    p1.MoveTo(250 + 350, 250);  getchar();
    l1.MoveLine(50, 20);        getchar();
    t1.MoveTri(-20, 30);        getchar();
    pr1.MovePrism(40, -10);     getchar();

    std::cout << "\nГеометрические параметры:\n";
    std::cout << "Длина отрезка: " << l1.Length() << std::endl;
    std::cout << "Периметр треугольника: " << t1.Perimeter() << std::endl;
    std::cout << "Площадь треугольника: " << t1.Area() << std::endl;
    std::cout << "Объём призмы: " << pr1.Volume() << std::endl;

    std::cout << "\nНажмите любую клавишу для завершения...";
    getchar();
    CloseWindow(hwnd);
    return 0;
}
