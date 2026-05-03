#include <windows.h>
#include <iostream>
#include <math.h>

HDC hdc;

class Point
{
protected:
    short x, y;
    size_t color;
public:
    Point();
    Point(short x, short y);
    Point(short x, short y, size_t color);

    short GetX();
    short GetY();
    size_t GetColor();
    void PutX(short newX);
    void PutY(short newY);
    void PutColor(size_t newColor);

    void Show();
    void Hide();
    void Move(short dx, short dy);
};

Point p1;                          // вызов первого
Point p2(100, 200);                // вызов второго
Point p3(300, 400, RGB(255, 0, 0));  // вызов третьего

class Line : public Point
{
protected:
    short x2, y2;
public:
    Line();
    Line(short x1, short y1, short x2, short y2);
    Line(short x1, short y1, short x2, short y2, size_t color);

    short GetX2();
    short GetY2();
    void PutX2(short newX2);
    void PutY2(short newY2);

    void Show();   // переопределение
    void Hide();   // переопределение
    void Move(short dx, short dy);  // переопределение

    float Length();
};

class Triangle : public Line
{
protected:
    short x3, y3;
public:
    Triangle();
    Triangle(short x1, short y1, short x2, short y2, short x3, short y3);
    Triangle(short x1, short y1, short x2, short y2,
        short x3, short y3, size_t color);

    short GetX3();
    short GetY3();
    void PutX3(short newX3);
    void PutY3(short newY3);

    void Show();   // переопределение
    void Hide();   // переопределение
    void Move(short dx, short dy);  // переопределение

    float Area();
};

class TriPrism : public Triangle
{
protected:
    short H;
public:
    TriPrism();
    TriPrism(short x1, short y1, short x2, short y2,
        short x3, short y3, short H);
    TriPrism(short x1, short y1, short x2, short y2,
        short x3, short y3, short H, size_t color);

    short GetH();
    void PutH(short newH);

    void Show();   // переопределение
    void Hide();   // переопределение
    void Move(short dx, short dy);  // переопределение

    float Volume();
};

Point::Point()
{
    x = 800;
    y = 450;
    color = RGB(127, 127, 127);
}

Point::Point(short x, short y)
{
    this->x = x;
    this->y = y;
    color = RGB(127, 127, 127);
}

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

void Point::Move(short dx, short dy)
{
    Hide();
    x += dx;
    y += dy;
    Show();
}


Line::Line() : Point()
{
    x2 = 900;
    y2 = 550;
}

Line::Line(short x1, short y1, short x2, short y2)
    : Point(x1, y1)
{
    this->x2 = x2;
    this->y2 = y2;
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

void Line::Show()
{
    HPEN pen = CreatePen(PS_SOLID, 2, (COLORREF)color);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x2, y2);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

void Line::Hide()
{
    size_t temp = color;
    color = RGB(241, 241, 241);
    Show();
    color = temp;
}

void Line::Move(short dx, short dy)
{
    Hide();
    x += dx;  y += dy;
    x2 += dx;  y2 += dy;
    Show();
}

float Line::Length()
{
    short dx = x2 - x;
    short dy = y2 - y;
    return sqrtf((float)(dx * dx + dy * dy));
}

Triangle::Triangle() : Line()
{
    x3 = 850;
    y3 = 600;
}

Triangle::Triangle(short x1, short y1, short x2, short y2,
    short x3, short y3)
    : Line(x1, y1, x2, y2)
{
    this->x3 = x3;
    this->y3 = y3;
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

void Triangle::Show()
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

void Triangle::Hide()
{
    size_t temp = color;
    color = RGB(241, 241, 241);
    Show();
    color = temp;
}

void Triangle::Move(short dx, short dy)
{
    Hide();
    x += dx;  y += dy;
    x2 += dx;  y2 += dy;
    x3 += dx;  y3 += dy;
    Show();
}

float Triangle::Area()
{
    float s = (float)(x * (y2 - y3) + x2 * (y3 - y) + x3 * (y - y2));
    return fabsf(s) / 2.0f;
}

TriPrism::TriPrism() : Triangle()
{
    H = 30;
}

TriPrism::TriPrism(short x1, short y1, short x2, short y2,
    short x3, short y3, short H)
    : Triangle(x1, y1, x2, y2, x3, y3)
{
    this->H = H;
}

TriPrism::TriPrism(short x1, short y1, short x2, short y2,
    short x3, short y3, short H, size_t color)
    : Triangle(x1, y1, x2, y2, x3, y3, color)
{
    this->H = H;
}

short TriPrism::GetH() { return H; }
void TriPrism::PutH(short newH) { H = newH; }

void TriPrism::Show()
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

void TriPrism::Hide()
{
    size_t temp = color;
    color = RGB(241, 241, 241);
    Show();
    color = temp;
}

void TriPrism::Move(short dx, short dy)
{
    Hide();
    x += dx;  y += dy;
    x2 += dx;  y2 += dy;
    x3 += dx;  y3 += dy;
    Show();
}

float TriPrism::Volume()
{
    return Area() * (float)H;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    SetConsoleCP(1251);
    system("color F0");

    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL) return 1;
    hdc = GetWindowDC(hwnd);
    if (hdc == NULL) return 1;

    std::cout << "Lab 3 - Polymorphism" << std::endl;
    std::cout << "Override + Overload" << std::endl;
    std::cout << std::endl;

    int SHIFT = 800;

    // === 4 объекта, созданных через ПОЛНЫЕ конструкторы ===
    Point    p(100 + SHIFT, 100, RGB(255, 0, 0));
    Line     l(180 + SHIFT, 100, 280 + SHIFT, 200, RGB(0, 180, 0));
    Triangle t(350 + SHIFT, 100, 470 + SHIFT, 100, 410 + SHIFT, 220, RGB(0, 0, 255));
    TriPrism tp(100 + SHIFT, 280, 220 + SHIFT, 280, 160 + SHIFT, 400, 40, RGB(150, 0, 150));

    std::cout << "Press ENTER to draw all objects via Show()..." << std::endl;
    getchar();

    // Каждый объект вызывает СВОЙ Show() благодаря переопределению
    p.Show();
    l.Show();
    t.Show();
    tp.Show();

    std::cout << std::endl
        << "All objects drawn correctly through unified Show() method." << std::endl
        << "(In Lab 2 calling t.Show() would draw only a point - now fixed by override)" << std::endl;

    std::cout << std::endl << "Press ENTER for movement demo..." << std::endl;
    getchar();

    for (int i = 0; i < 15; i++)
    {
        p.Move(2, 1);
        l.Move(1, 2);
        t.Move(2, 1);
        tp.Move(1, 1);
        Sleep(50);
    }

    // === Демонстрация полиморфных конструкторов ===
    std::cout << std::endl
        << "=== Overloaded constructors demo ===" << std::endl
        << "Creating objects with different argument counts..." << std::endl;
    std::cout << "Press ENTER..." << std::endl;
    getchar();

    // Конструктор без аргументов - всё по умолчанию
    Point pDef;
    pDef.PutX(450 + SHIFT);
    pDef.PutY(480);
    pDef.Show();

    // Конструктор с координатами, цвет по умолчанию (серый)
    Line lShort(500 + SHIFT, 480, 600 + SHIFT, 530);
    lShort.Show();

    // Конструктор с координатами, цвет по умолчанию
    Triangle tShort(380 + SHIFT, 480, 460 + SHIFT, 480, 420 + SHIFT, 560);
    tShort.Show();

    // Конструктор без аргументов - призма с дефолтными значениями
    TriPrism tpDef;
    tpDef.Show();

    std::cout << std::endl
        << "Created: gray point, gray line, gray triangle - default colors" << std::endl
        << "And one fully-default prism in the center of screen." << std::endl;

    std::cout << std::endl
        << "=== Geometric parameters ===" << std::endl;
    std::cout << "Line length:    " << l.Length() << std::endl;
    std::cout << "Triangle area:  " << t.Area() << std::endl;
    std::cout << "Prism volume:   " << tp.Volume() << std::endl;

    std::cout << std::endl << "Press ENTER to exit..." << std::endl;
    getchar();

    ReleaseDC(hwnd, hdc);
    return 0;
}