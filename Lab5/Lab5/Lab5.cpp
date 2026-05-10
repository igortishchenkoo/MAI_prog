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

// Абстрактный класс-интерфейс (модель interface из методички)
class ILocation {
public:
    virtual short GetX() = 0;
    virtual short GetY() = 0;
    virtual void PutX(short x) = 0;
    virtual void PutY(short y) = 0;
    virtual COLORREF GetC() = 0;
    virtual void PutC(COLORREF c) = 0;
    virtual void Show() = 0;
};

class Location : public ILocation {
protected:
    short X, Y;
public:
    Location(short x = 0, short y = 0) : X(x), Y(y) {}
    short GetX() override { return X; }
    short GetY() override { return Y; }
    void PutX(short x) override { X = x; }
    void PutY(short y) override { Y = y; }
    // Show, GetC, PutC остаются чисто виртуальными (абстрактный класс)
    virtual void Show() = 0;
};

class Point : public Location {
protected:
    COLORREF C;
public:
    Point(short x = 0, short y = 0, COLORREF c = RGB(0, 0, 0))
        : Location(x, y), C(c) {
    }
    COLORREF GetC() override { return C; }
    void PutC(COLORREF c) override { C = c; }
    void Show() override {
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

class Line : public Point {
protected:
    short X2, Y2;
public:
    Line(short x1 = 0, short y1 = 0, short x2 = 0, short y2 = 0, COLORREF c = RGB(0, 0, 0))
        : Point(x1, y1, c), X2(x2), Y2(y2) {
    }
    short GetX2() const { return X2; }
    short GetY2() const { return Y2; }
    void PutX2(short x) { X2 = x; }
    void PutY2(short y) { Y2 = y; }
    void Show() override {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);
        DeleteObject(pen);
    }
    double Length() const {
        return sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
    }
};

class Triangle : public Line {
protected:
    short X3, Y3;
public:
    Triangle(short x1 = 0, short y1 = 0, short x2 = 0, short y2 = 0,
        short x3 = 0, short y3 = 0, COLORREF c = RGB(0, 0, 0))
        : Line(x1, y1, x2, y2, c), X3(x3), Y3(y3) {
    }
    short GetX3() const { return X3; }
    short GetY3() const { return Y3; }
    void PutX3(short x) { X3 = x; }
    void PutY3(short y) { Y3 = y; }
    void Show() override {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);
        DrawLine(hdc, X2, Y2, X3, Y3);
        DrawLine(hdc, X3, Y3, X, Y);
        DeleteObject(pen);
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
    TriangularPrism(short x1 = 0, short y1 = 0, short x2 = 0, short y2 = 0,
        short x3 = 0, short y3 = 0, short height = 0, COLORREF c = RGB(0, 0, 0))
        : Triangle(x1, y1, x2, y2, x3, y3, c), Height(height) {
    }
    short GetHeight() const { return Height; }
    void PutHeight(short h) { Height = h; }
    void Show() override {
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
    double Volume() const {
        return Area() * Height;
    }
};

void Clear(ILocation* pObj) {
    COLORREF oldC = pObj->GetC();
    pObj->PutC(RGB(241, 241, 241));
    pObj->Show();
    pObj->PutC(oldC);
}

void Move(short nx, short ny, ILocation* pObj) {
    Clear(pObj);
    pObj->PutX(nx);
    pObj->PutY(ny);
    pObj->Show();
}

int main() {
    system("color f0");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();
    hdc = GetWindowDC(hwnd);

    std::cout << "Лаб.раб.№5. Абстрактные классы. Интерфейс. Полиморфные объекты.\n";

    Point* pP1 = new Point(200 + 350, 400, RGB(255, 0, 0));
    Point* pP2 = new Point(800, 160, RGB(0, 128, 255));
    Line* pL1 = new Line(200 + 350, 350, 350 + 350, 400, RGB(0, 0, 255));
    Triangle* pT1 = new Triangle(400 + 350, 300, 500 + 350, 400, 450 + 350, 500, RGB(0, 128, 0));
    TriangularPrism* pPr1 = new TriangularPrism(550 + 350, 350, 650 + 350, 380, 600 + 350, 450, 70, RGB(255, 0, 255));

    std::cout << "1. Вызов Show через интерфейсный указатель:\n";
    pP1->Show(); getchar();
    pL1->Show(); getchar();
    pT1->Show(); getchar();
    pPr1->Show(); getchar();

    std::cout << "2. Работа с полиморфными функциями Clear и Move:\n";
    ILocation* pLoc;
    pLoc = pP1;   Move(250 + 350, 450, pLoc); getchar();
    pLoc = pL1;   Move(250 + 350, 380, pLoc); getchar();
    pLoc = pT1;   Move(450 + 350, 350, pLoc); getchar();
    pLoc = pPr1;  Move(600 + 350, 400, pLoc); getchar();

    std::cout << "Геометрические параметры:\n";
    std::cout << "Длина отрезка: " << pL1->Length() << "\n";
    std::cout << "Периметр треугольника: " << pT1->Perimeter() << "\n";
    std::cout << "Площадь треугольника: " << pT1->Area() << "\n";
    std::cout << "Объём призмы: " << pPr1->Volume() << "\n";

    delete pP1; delete pP2;
    delete pL1; delete pT1; delete pPr1;

    std::cout << "\nЗавершение..."; getchar();
    CloseWindow(hwnd);
    return 0;
}