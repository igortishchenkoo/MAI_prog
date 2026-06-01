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

    virtual void Show() {
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
    Line(short x1 = 0, short y1 = 0, short x2 = 0, short y2 = 0, size_t c = RGB(0, 0, 0))
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
        short x3 = 0, short y3 = 0, size_t c = RGB(0, 0, 0))
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
        short x3 = 0, short y3 = 0, short height = 0, size_t c = RGB(0, 0, 0))
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

int main() {
    system("color f0");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();
    hdc = GetWindowDC(hwnd);

    std::cout << "Ћаб.раб.є4. ¬иртуальные функции. ¬ариант 7\n";

    Point pt(200 + 350, 400, RGB(255, 0, 0));
    Line ln(200 + 350, 350, 350 + 350, 400, RGB(0, 0, 255));
    Triangle tr(400 + 350, 300, 500 + 350, 400, 450 + 350, 500, RGB(0, 128, 0));
    TriangularPrism pr(550 + 350, 350, 650 + 350, 380, 600 + 350, 450, 70, RGB(255, 0, 255));

    std::cout << "1. Show() Ц виртуальный, рисует все фигуры корректно:\n";
    pt.Show();   getchar();
    ln.Show();   getchar();
    tr.Show();   getchar();
    pr.Show();   getchar();

    std::cout << "2. Hide() Ц работает через виртуальный Show, стирает:\n";
    pt.Hide();   getchar();
    ln.Hide();   getchar();
    tr.Hide();   getchar();
    pr.Hide();   getchar();

    pt.Show(); ln.Show(); tr.Show(); pr.Show(); getchar();

    std::cout << "3. MoveTo() Ц использует Hide/Show, двигает:\n";
    pt.MoveTo(250 + 350, 450); getchar();
    ln.MoveTo(250 + 350, 380); getchar();
    tr.MoveTo(450 + 350, 350); getchar();
    pr.MoveTo(600 + 350, 400); getchar();

    std::cout << "4. ¬иртуальный вызов через массив Point*:\n";
    Point* figures[4] = { &pt, &ln, &tr, &pr };
    for (int i = 0; i < 4; ++i) {
        figures[i]->Show();
        getchar();
    }

    std::cout << "√еометрические параметры:\n";
    std::cout << "ƒлина отрезка: " << ln.Length() << "\n";
    std::cout << "ѕериметр треугольника: " << tr.Perimeter() << "\n";
    std::cout << "ѕлощадь треугольника: " << tr.Area() << "\n";
    std::cout << "ќбъЄм призмы: " << pr.Volume() << "\n";

    std::cout << "\n«авершение..."; getchar();
    CloseWindow(hwnd);
    return 0;
}
